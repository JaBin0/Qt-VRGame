#ifndef GAME_H
#define GAME_H

// Qt headers
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

// Own headers

// Forward declaration
class QQuickWindow;
class GameRenderer;
class GameContent;

class Game : public QQuickItem
{
    Q_OBJECT
//    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    // Constructors & Destructor
    Game();
    ~Game();

private slots:
    // Initialize Game module
    void init();

    // Draw one full frame of the game
    void drawGame();

    // Slots invoke when window connected to the game changed
    void onWindowChanged(QQuickWindow* window);

    // Handle change of the main window size
    void onWindowSizeChanged(int);



private: // Atributes
    // Handler for the game renderer
    GameRenderer* m_renderer;

    // Content of the game
    GameContent* m_content;

    // Main window handler
    QQuickWindow *m_window;

//    qreal t() const { return m_t; }
//    void setT(qreal t);
//signals:
//    void tChanged();

//public slots:
//    void sync();
//    void cleanup();

//private slots:
//    void handleWindowChanged(QQuickWindow *win);

//private:
//    qreal m_t;
//    SquircleRenderer *m_renderer;
};

#endif // GAME_H
