#ifndef GAME_H
#define GAME_H
// Qt headers
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLFunctions>
// Own header
#include <GraphicTypes.h>

// Forward declaration
class GameRenderer;
class GameRscManager;

class Game : public QQuickItem {

public:
    // Constructors && Destructor
    Game();
    ~Game();

protected slots:
    // Reaction to the window change singal
    void onWindowChanged(QQuickWindow* window);

    // Reaction to the change of the window size hight and width
    void onWindowSizeChanged(int);

    // Method which will be called when openGL context, of the window will be initialized,
    // This is method which will actualy initialize whole game
    void init();

    // Process one frame drawing
    void drawFrame();

protected: // Members
    // Resource manager
    GameRscManager* m_rscManager;

    // Graphic renderer
    GameRenderer* m_renderer;

    // Path to the default game scne file
    static const QString LEVEL_FILE_PATH;

    QList<ContentPart*>* pContent;

};

#endif // GAME_H
