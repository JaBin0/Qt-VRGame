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
    enum MODELEXT {
        OBJ = 0,
        MODELEXT_COUNT
    };


    // Constructor & Destructor
    GameResourcesManager();
    ~GameResourcesManager();

    // Load shaders form external resources
    void loadShaderSources(const QString configPath, ShaderSourcMap &shaderSrcMap);

    // General method for loading any type of the model, which is supported.
    void loadModel(QString modelPath, QVector<float>& modelData);

    // Load and parse OBJ model
    void load_obj_model(QFile& model, QVector<float>& modelData);

protected:
    // Mapping model extension name to the integer representaion
    QMap<QString, MODELEXT> m_extDictionary;
};

#endif // GAMERESOURCESMANAGER_H
