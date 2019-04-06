#ifndef GAMERESOURCESMANAGER_H
#define GAMERESOURCESMANAGER_H
// Qt headers
#include <QString>
#include <QMap>
#include <QPair>

// Own headers
#include <SystemTypes.h>

class GameResourcesManager
{
public:
    // Constructor & Destructor
    GameResourcesManager();
    ~GameResourcesManager();

    // Load shaders form external resources
    void loadShaderSources(const QString configPath, ShaderSourcMap &shaderSrcMap);
};

#endif // GAMERESOURCESMANAGER_H
