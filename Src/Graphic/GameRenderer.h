#ifndef GAMERENDERER_H
#define GAMERENDERER_H
// Qt headers
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>



class GameRenderer: public QObject, protected QOpenGLFunctions
{
public:
    // Constructors & Destructor
    GameRenderer();
    ~GameRenderer();

    // Return current window used by renderer for drawing
    const QQuickWindow* window();

public slots:
    // Slots invoke when window connected to the game changed
    void onWindowChanged(QQuickWindow* window);

    // Slots invoke when window size changed
    void onWindowSizeChanged();

private slots:
    // Draw scene on the window surface
    void drawScene();

protected:
    QQuickWindow *m_window;

//    void setT(qreal t) { m_t = t; }
//    void setViewportSize(const QSize &size) { m_viewportSize = size; }
//    void setWindow(QQuickWindow *window) { m_window = window; }

//public slots:
//    void paint();

//private:
//    QSize m_viewportSize;
//    qreal m_t;
//    QOpenGLShaderProgram *m_program;
//    QQuickWindow *m_window;

};

#endif // GAMERENDERER_H
