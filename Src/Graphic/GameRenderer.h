#ifndef GAMERENDERER_H
#define GAMERENDERER_H

// Qt headers
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

// Forward declaration
class GameContent;

class GameRenderer: public QObject, protected QOpenGLFunctions
{
public:
    // Constructors & Destructor
    GameRenderer();
    ~GameRenderer();

    // Initialize game renderer module
    void init();

    // Draw given content
    void draw(GameContent* content);

private:
    // Graphic pipline id
    uint m_programId;

    // Geometric representation of the test triangle
    float* m_triangle;
};

#endif // GAMERENDERER_H
