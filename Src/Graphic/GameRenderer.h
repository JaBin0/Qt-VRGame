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
    void draw(GameContent* content, QQuickWindow* window);

private:
    // Graphic pipline id
    uint m_programId;

    // Vertex array object
    uint vbo;

    uint m_cubeVBO;

    // Geometric representation of the test triangle
    float* m_triangle;

    float* m_cube;
};

#endif // GAMERENDERER_H
