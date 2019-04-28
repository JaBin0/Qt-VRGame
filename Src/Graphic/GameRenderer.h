#ifndef GAMERENDERER_H
#define GAMERENDERER_H
// Qt headers
#include <QMatrix4x4>
#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLFunctions>
// Own headers
#include <GraphicTypes.h>
//#include <QtGui/QOpenGLShaderProgram>

// Forward declaration
class GameContent;
class GameResourcesManager;

class GameRenderer: public QObject, protected QOpenGLFunctions
{
public:
    // Constructors & Destructor
    GameRenderer(QQuickWindow* window);
    GameRenderer() = delete;
    ~GameRenderer();

    // Create model
    void createModel(ModelTemplate* modelTemp);

    // Create shader map based on the given sources
    void initShaders(QMap<QString, QPair<QString, QString>>* shaderSourcesMap);

    // Initialize game renderer module
//    void init(GameResourcesManager* const resMgrCallback, QQuickWindow* window);

//    // Draw given content
//    void draw(GameContent* content, QQuickWindow* window);

    // Render frame based on the given content
    void renderFrame(QList<ContentPart*>* content);

    // Render frame based on the given content
    void renderObject(QString modelName);

    // Render part of the screen UI
    void renderUI();

    // Delete model template information
    void deleteModelTemplate(ModelTemplate* model);

    // Set size of the window for the window
    void setViewPort(QSize size);

protected:
    // Create Texture
    uint createTexture(const QString textureName);

    // Create vertex buffer object
    uint createVBO(QVector<float> *data);

    // Create Graphic pipline based on the given vertex and fragment shaders sources.
    // Handler to the new created graphic pipline is returned
    uint createGraphicPipline(const QString vertShaderSource, const QString fragShaderSource, uint& err);

private:
    // Perspective matirx
    QMatrix4x4 m_perspective;

    // Orthogonometic matrix
    QMatrix4x4 m_ortho;

    // List of supported models
    QMap<QString, Model*> models;

    // List of supported models
    QMap<QString, uint> shaders;

//    // Map which connect graphic pipleine program name with it's handler
//    QMap <QString, uint> m_shadersMap;

//    // Test texture
//    uint m_texture;

//    // Size of the model
//    uint m_size;

//    // Graphic pipline id
//    uint m_programId;

//    // Vertex array object
//    uint vbo;

//    uint m_cubeVBO;

//    // Geometric representation of the test triangle
//    float* m_triangle;

//    float* m_cube;

//    // Paths for shader configs files for Desktop and for Android devices
//    static const QString SHADERS_CFG_DESKTOP;
//    static const QString SHADERS_CFG_ANDROID;
};

#endif // GAMERENDERER_H
