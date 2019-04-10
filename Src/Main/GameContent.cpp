// Qt headers
#include <QMatrix4x4>

// Own headers
#include <GameContent.h>


GameContent::GameContent()
{

}

void GameContent::createScence()
{
    QVector3D pos(2.0, 1.0, -4.0);
    m_sceneContent.push_back(new BasicAsset(ASSET_TYPES::BASIC, pos));

    QVector3D pos2(-2.0, 1.0, -4.0);
    m_sceneContent.push_back(new BasicAsset(ASSET_TYPES::BASIC, pos2));
}
