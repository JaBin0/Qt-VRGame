
// Qt header
#include <QFile>
#include <QPair>
#include <QVector3D>
#include <QList>

// System headers
#include <iostream>

// Own headers
#include <SysMethods.h>
#include <GameResourcesManager.h>

GameResourcesManager::GameResourcesManager() {
    m_extDictionary.insert("obj", OBJ);
}

GameResourcesManager::~GameResourcesManager()
{
    std::cout << "~GameResourcesManager" << std::endl;
}

void GameResourcesManager::loadShaderSources(const QString configPath, ShaderSourcMap& shaderSrcMap)
{
    std::cout << "Loading Shaders sources ............. ";
    uint err = 0;

    // Loading shaders
    QFile cfg(configPath);
    if(!cfg.exists()) {
        err = 1;
        std::cout << "ERROR::RESOURCE_MANAGER::CONFIG_FILE_NOT_EXIST:\n" << configPath.toUtf8().constData() << std::endl;
        std::cout << "faild with error - " << err << std::endl;
        return;
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
            shaderSrcMap.insert(name, QPair<QString, QString>(QString(vertexShader.readAll()), QString(fragmentShader.readAll())));
            vertexShader.close();
            fragmentShader.close();
        }
    }
    cfg.close();
    SysMethods::errorCheck(err);
}

void GameResourcesManager::loadModel(QString modelPath, QVector<float>& modelData) {
    QFile model(modelPath);
    if(!model.exists()) {
        std::cout << "ERROR::RESOURCE_MANAGER::FILE_NOT_EXIST:\n" << modelPath.toStdString().data() << std::endl;
        return;
    }

    // Get model extension. +1 to ommit symbol '.'
    int index = modelPath.lastIndexOf(".")+1;
    QString extension = modelPath.right(modelPath.length() - index);

    switch(m_extDictionary.value(extension)) {
    case OBJ: {
        load_obj_model(model, modelData);
    }
        break;
    default: {

    }
    };

    std::cout << "Ext: " << extension.toStdString().data() << std::endl;

}

void GameResourcesManager::load_obj_model(QFile &model, QVector<float>& modelData) {
    model.open(QIODevice::ReadOnly);
    QList<QVector3D> vertexCoords;
    QList<QVector3D> normalsCoords;
    QList<QVector2D> textureCoords;

    while(!model.atEnd()) {
        QString line (model.readLine());
        line = line.trimmed();

        // Separete content form tag
        int tagIndex = line.indexOf(" ");
        QString tag = line.left(tagIndex);
        line = line.right(line.length() - (tagIndex + 1));

        if(tag == "v") {
            QStringList dataStr = line.split(" ");
            vertexCoords.append(QVector3D(dataStr.at(0).toFloat(), dataStr.at(1).toFloat(), dataStr.at(2).toFloat()));
        }
        else if (tag == "vt") {
            QStringList dataStr = line.split(" ");
            textureCoords.append(QVector2D(dataStr.at(0).toFloat(), dataStr.at(1).toFloat()));
        }
        else if (tag == "vn") {
            QStringList dataStr = line.split(" ");
            normalsCoords.append(QVector3D(dataStr.at(0).toFloat(), dataStr.at(1).toFloat(), dataStr.at(2).toFloat()));
        }
        else if(tag == "f") {
            QStringList faceVertex = line.split(" ");
            for(QString vertex : faceVertex) {
                QStringList vertexData = vertex.split("/");

                int vertexCoordIndex = vertexData.at(0).toInt() - 1;
                QVector3D vertexGeoData = vertexCoords.at(vertexCoordIndex);
                modelData.append(vertexGeoData.x());
                modelData.append(vertexGeoData.y());
                modelData.append(vertexGeoData.z());

                int normalCoordIndex = vertexData.at(2).toInt() - 1;
                QVector3D normalData = normalsCoords.at(normalCoordIndex);
                modelData.append(normalData.x());
                modelData.append(normalData.y());
                modelData.append(normalData.z());

                int textureCoordIndex = vertexData.at(1).toInt() - 1;
                QVector2D textureData = textureCoords.at(textureCoordIndex);
                modelData.append(textureData.x());
                modelData.append(textureData.y());

            }
        }
        else {
            // Different tag probably o or # which should not create any reaction
        }
    }

    model.close();
}
