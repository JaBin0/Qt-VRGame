#ifndef GAMERENDERER_H
#define GAMERENDERER_H

// Qt headers
#include <QMatrix4x4>
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

// Forward declaration
class GameContent;
class GameResourcesManager;

class GameRenderer: public QObject, protected QOpenGLFunctions
{
public:
    // Constructors & Destructor
    GameRenderer();
    ~GameRenderer();

    // Initialize game renderer module
    void init(GameResourcesManager* const resMgrCallback, QQuickWindow* window);

    // Draw given content
    void draw(GameContent* content, QQuickWindow* window);

    // Set size of the window for the window
    void setViewPort(QSize size);

protected:
    // Create Graphic pipline based on the given vertex and fragment shaders sources.
    // Handler to the new created graphic pipline is returned
    uint createGraphicPipline(const QString vertShaderSource, const QString fragShaderSource, uint& err);

private:
    // Perspective matirx
    QMatrix4x4 m_perspective;

    // Map which connect graphic pipleine program name with it's handler
    QMap <QString, uint> m_shadersMap;

    // Test texture
    uint m_texture;


    // Graphic pipline id
    uint m_programId;

    // Vertex array object
    uint vbo;

    uint m_cubeVBO;

    // Geometric representation of the test triangle
    float* m_triangle;

    float* m_cube;

    // Paths for shader configs files for Desktop and for Android devices
    static const QString SHADERS_CFG_DESKTOP;
    static const QString SHADERS_CFG_ANDROID;
};

#endif // GAMERENDERER_H
