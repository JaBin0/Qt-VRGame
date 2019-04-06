
// Qt header
#include <QFile>
#include <QPair>

// System headers
#include <iostream>

// Own headers
#include <SysMethods.h>
#include <GameResourcesManager.h>

GameResourcesManager::GameResourcesManager() {

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
