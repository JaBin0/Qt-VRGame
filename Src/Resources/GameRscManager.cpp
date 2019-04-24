// Qt headers
#include <QFile>
#include <QVector2D>
#include <QMatrix4x4>
#include <QStringList>
#include <QDomDocument>
// System headers
#include <iostream>
// Own headers
#include <Asset.h>
#include <DaeTagsDictionary.h>
#include <ResourcesTypes.h>
#include <GameRscManager.h>


// static variables
const QString GameRscManager::IMAGE_PATH = ":/Assets/Textures/";
const QString GameRscManager::ASSET_PATH = ":/Assets/Models/dae/";

GameRscManager::GameRscManager() {

}

GameRscManager::~GameRscManager() {

}

ModelTemplate* GameRscManager::loadModel_Dae(QString filePath, RSC_ERROR &err) {
    ModelTemplate* ret = new ModelTemplate();
    QDomDocument* daeDoc = load_XmlFile(filePath);
    if(nullptr != daeDoc) {
        QDomElement visualScene = daeDoc->documentElement().firstChildElement("library_visual_scenes").firstChildElement();
        if(visualScene.isNull()) {
            std::cout << "There is no visual_scenes element in library_visual_scenes" << std::endl;
            return nullptr;
        }
        // Get object Id
        QDomElement object = visualScene.firstChildElement();
        ret->id = object.attribute("id");

        // Get object transformation
        QVector<float> dataVector;
        for(auto data : object.firstChildElement("matrix").firstChild().nodeValue().split(" ")) {
            dataVector.push_back(data.toFloat());
        };
        ret->trans = new QMatrix4x4(dataVector.data());

        // Get geometry instance
        QString geometryUrl = object.firstChildElement("instance_geometry").attribute("url").remove(0,1);
        QDomElement geometryNode = daeDoc->documentElement().firstChildElement("library_geometries").firstChildElement();
        if(geometryUrl != geometryNode.attribute("id")) {
            std::cout << "There is no geometry with id: " << geometryUrl.toUtf8().constData() << std::endl;
            return nullptr;
        }
        QDomNode mesh = geometryNode.firstChild();

        // Get postion list
        QDomNode source = mesh.firstChild();
        QVector<QVector3D> postions;
        QStringList data = source.firstChildElement("float_array").firstChild().nodeValue().split(" ");
        for(int idx = 0; idx < data.length(); idx+=3) {
            postions.push_back(QVector3D(data.at(idx).toFloat(), data.at(idx+1).toFloat(), data.at(idx+2).toFloat()));
        }

        // Get normals
        source=source.nextSibling();
        QVector<QVector3D> normals;
        data = source.firstChildElement("float_array").firstChild().nodeValue().split(" ");
        for(int idx = 0; idx < data.length(); idx+=3) {
            normals.push_back(QVector3D(data.at(idx).toFloat(), data.at(idx+1).toFloat(), data.at(idx+2).toFloat()));
        }

        // Get texture coords
        source=source.nextSibling();
        QVector<QVector2D> texCoords;
        data = source.firstChildElement("float_array").firstChild().nodeValue().split(" ");
        for(int idx = 0; idx < data.length(); idx+=2) {
            texCoords.push_back(QVector2D(data.at(idx).toFloat(), data.at(idx+1).toFloat()));
        }

        // Create buffer
        QVector<float>* buffer = new QVector<float>();
        QDomElement triangle = mesh.firstChildElement("triangles");
        QStringList p = triangle.firstChildElement("p").firstChild().nodeValue().split(" ");
        for(int idx = 0; idx < p.length(); idx+=3) {
            QVector3D postion = postions.at(p.at(idx).toInt());
            buffer->push_back(postion.x());
            buffer->push_back(postion.y());
            buffer->push_back(postion.z());
            QVector3D normal = normals.at(p.at(idx+1).toInt());
            buffer->push_back(normal.x());
            buffer->push_back(normal.y());
            buffer->push_back(normal.z());
            QVector2D texCoord = texCoords.at(p.at(idx+2).toInt());
            buffer->push_back(texCoord.x());
            buffer->push_back(texCoord.y());
        }
        ret->data = buffer;

        // Get material
        QString materialId = triangle.attribute("material");
        QDomNode imageNode = daeDoc->documentElement().firstChildElement("library_images").firstChildElement().firstChild().firstChild();
        ret->image = imageNode.nodeValue();

        delete daeDoc;
    }
    return ret;
}

QMap<QString, QPair<QString, QString>>* GameRscManager::loadShaderSources(const QString configPath) {
    auto* resultShaderMap = new QMap<QString, QPair<QString, QString>>();
    uint err = 0;

    // Loading shaders
    QFile cfg(configPath);
    if(!cfg.exists()) {
        err = 1;
        std::cout << "ERROR::RESOURCE_MANAGER::CONFIG_FILE_NOT_EXIST:\n" << configPath.toUtf8().constData() << std::endl;
        std::cout << "faild with error - " << err << std::endl;
        return nullptr;
    }

    // Get path to folder, +1 to include last symbol /
    QString folderPath = configPath.left(configPath.lastIndexOf("/") + 1);

    cfg.open(QIODevice::ReadOnly);
    while(!cfg.atEnd()) {
        QString line(cfg.readLine());
        line = line.trimmed();
        if(line.startsWith("[")) {
            // Get length of specific tags markers -/+ 1 is ment to avoid tag symbol
            int nameLength = line.indexOf("]") - 1;
            int filePairTagBegin = line.indexOf("<") + 1;
            int filePairLength = line.indexOf(">") - filePairTagBegin;

            // Get tag content, extpected format:
            // [name]<vertexName.gls, fragmentName.gls>
            QString name = line.mid(1, nameLength);
            QString filesPair = line.mid(filePairTagBegin, filePairLength);
            QStringList fileList = filesPair.split(",");
            QString vertShaderName = fileList.at(0).trimmed();
            QString fragShaderName = fileList.at(1).trimmed();

            QFile vertexShader(folderPath + vertShaderName);
            QFile fragmentShader(folderPath + fragShaderName);
            if(!vertexShader.exists() || !fragmentShader.exists()) {
                err = 2;
                std::cout << "\nERROR::RESOURCE_MANAGER::NO_SHADER_FILES_IN_SET:\n" << line.toStdString().data() << std::endl;
                continue;
            }

            // Open and insert shaders source to the map. Close files at the end.
            vertexShader.open(QIODevice::ReadOnly);
            fragmentShader.open(QIODevice::ReadOnly);
            resultShaderMap->insert(name, QPair<QString, QString>(QString(vertexShader.readAll()), QString(fragmentShader.readAll())));
            vertexShader.close();
            fragmentShader.close();
        }
    }
    cfg.close();
    return resultShaderMap;
}

QDomDocument *GameRscManager::load_XmlFile(const QString filePath) {
    QDomDocument* xmlDoc = new QDomDocument("Model");
    QFile xmlfile(filePath);
    if(!xmlfile.open(QIODevice::ReadOnly) || !xmlDoc->setContent(&xmlfile)) {
        std::cout << "ERROR::GameRscManager - " << filePath.toUtf8().constData() << " could not be loaded" << std::endl;
        xmlfile.close();
        return nullptr;
    }
    return xmlDoc;
}

QList<ContentPart*>* GameRscManager::load_Scene(const QString filePath) {
    auto* list = new QList<ContentPart*>();
    QDomDocument* daeDoc = load_XmlFile(filePath);
    if(nullptr != daeDoc) {
        std::cout << "Loading scne" << std::endl;
        QDomElement visual_scene = daeDoc->documentElement().firstChildElement("library_visual_scenes").firstChildElement("visual_scene");
        if(visual_scene.isNull()) {
            std::cout << "No library_visual_scenes::visual_scene node" << std::endl;
            return nullptr;
        }
        QDomNodeList nodes = visual_scene.childNodes();
        for(auto idx = 0; idx < nodes.length(); ++idx) {
            QDomElement node = nodes.at(idx).toElement();
            QString id = node.attribute("id");
            QVector<float> dataVector;
            for(auto data : node.firstChildElement("matrix").firstChild().nodeValue().split(" ")) {
                dataVector.push_back(data.toFloat());
            };
            list->push_back(new ContentPart{id, new QMatrix4x4(dataVector.data())});
        }
    }
    return list;
}


// ======================================================================================

//RSC_ERROR GameRscManager::load_Scene(const QString filePath) {
//    // TODO: Add system of loading ... success marker
//    QDomDocument sceneDoc("Scene");
//    QFile sceneFile (filePath);
//    if(!sceneFile.open(QIODevice::ReadOnly) || !sceneDoc.setContent(&sceneFile)) {
//        sceneFile.close();
//        return RSC_ERROR::FILE_NOT_PROCESSED;
//    }
//    QDomNode libNode = sceneDoc.documentElement().firstChild();
//    while(!libNode.isNull()) {
//        QDomElement libElem = libNode.toElement();
//        switch(daeTagsDict[libElem.tagName()]) {
//        case DAE::LIB_VISUAL_SCENES: {
//            // Take all child of the first nested node, iterate over them and create all assets
//            QDomNodeList assetList = libElem.firstChild().toElement().childNodes();
//            for(int idx = 0; idx < assetList.length(); ++idx) {
//                QDomElement assetElem = assetList.at(idx).toElement();

//                // Get ID of the model and its path to file
//                QString strId = assetElem.attribute("id");
//                load_DaeModel(Asset::str_to_modelId(strId));
//            }
//        }
//            break;
//        default: {
//            // Tag not supported -> Nothing to do here right now
//        }
//        };
//        // Take next sibling
//        libNode = libNode.nextSibling();
//    }


////    sceneFile.close();
//    return RSC_ERROR::NO_ERR;
//}

RSC_ERROR GameRscManager::load_DaeModel(const Asset::MODEL_ID id) {
//    // TODO check if model loaded

//    // Retrive model name
//    QString modelPath = ASSET_PATH + Asset::modelId_to_str(id) + ".dae";
//    QFile model(modelPath);
//    QDomDocument modelDoc("ModelDoc");

//    if(!model.open(QIODevice::ReadOnly)|| !modelDoc.setContent(&model)) {
//        std::cout << "File " << modelPath.toUtf8().constData() << " could not be loaded" << std::endl;
//        model.close();
//        return RSC_ERROR::MODEL_FILE_COULD_NOT_BE_PARSED;
//    }

//    QDomNode libNode = modelDoc.documentElement().firstChild();
//    while (!libNode.isNull()) {
//        QDomElement libElem = libNode.toElement();
//        switch(daeTagsDict[libElem.tagName()]) {
//        case DAE::LIB_VISUAL_SCENES: {
//            // Take all child of the first nested node, iterate over them and create all assets
//            QDomNodeList assetList = libElem.firstChild().toElement().childNodes();
//            for(int idx = 0; idx < assetList.length(); ++idx) {
//                QDomElement assetElem = assetList.at(idx).toElement();

//                // Get ID of the model and its path to file
//                QString strId = assetElem.attribute("id");
//                load_DaeModel(Asset::str_to_modelId(strId));
//            }
//        }
//            break;
//        default: {
//            // Tag not supported -> Nothing to do here right now
//        }
//        };

//        std::cout << "Model: " << libElem.tagName().toUtf8().constData() << std::endl;
//        libNode = libNode.nextSibling();
//    }


//    model.close();
    return RSC_ERROR::NO_ERR;
}




