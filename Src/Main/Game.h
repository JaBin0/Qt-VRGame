#ifndef GAME_H
#define GAME_H

// Qt headers
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

// Own headers

// Forward declaration
class GameRenderer;

class Game : public QQuickItem
{
    Q_OBJECT
//    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    // Constructors & Destructor
    Game();
    ~Game();

public slots:
    void test ();

private slots:
    // Handle change of the main window
    void handleWindowChanged(QQuickWindow *window);

private: // Atributes
    // Handler for the game renderer
    GameRenderer* m_renderer;


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
