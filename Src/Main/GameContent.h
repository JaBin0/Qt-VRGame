#ifndef GAMECONTENT_H
#define GAMECONTENT_H

// Qt headers
#include <QList>

// Own headers
#include <BasicAsset.h>

class GameContent
{
public:
    GameContent();

    // Create scene assets
    void createScence();

protected:
    // List to store all scene assets
    QList <BasicAsset*> m_sceneContent;


};

#endif // GAMECONTENT_H
