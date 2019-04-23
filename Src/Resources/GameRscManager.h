#ifndef GAMERSCMANAGER_H
#define GAMERSCMANAGER_H
// Qt headers
#include <QString>
#include <QDomDocument>
// Own headers
#include <Asset.h>
#include <GraphicTypes.h>


// Types
enum RSC_ERROR {
    NO_ERR = 0,
    FILE_NOT_PROCESSED,
    MODEL_FILE_NOT_EXIST,
    MODEL_FILE_COULD_NOT_BE_PARSED,
};

class GameRscManager
{

public:
    // Constructors && Destructor
    GameRscManager();
    ~GameRscManager();

    // Load Dae model and return pointer to new created element
    ModelTemplate* loadModel_Dae(QString filePath, RSC_ERROR& err);

    QMap<QString, QPair<QString, QString>>* loadShaderSources(const QString configPath);

    // load and parse scene file
   RSC_ERROR load_Scene(const QString filePath);

   // Check if model is already in resources, in case of no load it to the game
   RSC_ERROR load_DaeModel(const Asset::MODEL_ID id);
protected:
   // Load xml file and return QDocument
   QDomDocument* load_XmlFile(const QString filePath);

protected: // Members
   // Path to the assets files
   static const QString ASSET_PATH;

   // Path to the image which should be converted to the texture
   static const QString IMAGE_PATH;
};

#endif // GAMERSCMANAGER_H
