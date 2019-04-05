// Qt headers
#include <QQuickWindow>
#include <QOpenGLContext>
#include <QMatrix4x4>
#include <QVector3D>

// System headers
#include <iostream>
#include <string.h>

// Own headers
#include <GameRenderer.h>
#include <GameContent.h>

GameRenderer::GameRenderer()
    : m_programId {0}
    , m_triangle {nullptr}
    , m_cubeVBO(0)
{
    initializeOpenGLFunctions();
}

GameRenderer::~GameRenderer() {
    std::cout << "GameRenderer::Destructor" << std::endl;
}

void GameRenderer::init() {
    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);
    const char* vertexShaderSource = "attribute vec3 vPos;\n"
                                     "attribute vec3 vColor;\n"
                                     ""
                                     "varying vec3 fColor;\n"
                                     ""
                                     "uniform mat4 perspective;\n"
                                     "uniform mat4 lookAt;\n"
                                     ""
                                     "void main() {\n"
                                     "    gl_Position = perspective * lookAt *vec4(vPos, 1.0);\n"
                                     "    fColor = vColor;"
                                     "}\0";

    const char* fragmentShaderSource = "varying vec3 fColor;\n"
                                       "void main() {\n"
                                       "    gl_FragColor = vec4(fColor, 1.0);\n"
                                       "}\0";

    int success = 0;
    char infoLog[512];

    // Create Vertex Shader
    uint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShaderId);
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
        std::cout << "ERROR::VERTEX::SHADER::COMPILE_FAILD\n" << infoLog << std::endl;
    }

    // Create Fragment Shader
    uint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShaderId, 512, nullptr, infoLog);
        std::cout << "ERROR::FRAGMENT::SHADER::COMPILE_FAILD\n" << infoLog << std::endl;
    }

    // Create graphic pipline program
    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexShaderId);
    glAttachShader(m_programId, fragmentShaderId);
    glLinkProgram(m_programId);

    glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_programId, 512, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::LINKING_FAILD\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    m_triangle = new float[6] {
                    -0.5, -0.5,
                     0.0,  0.5,
                     0.5, -0.5,
                 };

    m_cube = new float[216]  {
                    // Front face
                     0.5, -0.5,  -4.5, 1.0, 0.0, 0.0,
                    -0.5, -0.5,  -3.5, 1.0, 0.0, 0.0,
                     0.5, -0.5,  -3.5, 1.0, 0.0, 0.0,

                     0.5, -0.5,  -4.5, 1.0, 0.0, 0.0,
                    -0.5, -0.5,  -4.5, 1.0, 0.0, 0.0,
                    -0.5, -0.5,  -3.5, 1.0, 0.0, 0.0,
                    // Second face
                    -0.5,  0.5,  -3.5, 0.0, 1.0, 0.0,
                     0.5,  0.5,  -4.5, 0.0, 1.0, 0.0,
                     0.5,  0.5,  -3.5, 0.0, 1.0, 0.0,

                    -0.5,  0.5,  -3.5, 0.0, 1.0, 0.0,
                    -0.5,  0.5,  -4.5, 0.0, 1.0, 0.0,
                     0.5,  0.5,  -4.5, 0.0, 1.0, 0.0,
                    // Third face
                     0.5,  0.5,  -3.5, 0.0, 0.0, 1.0,
                     0.5, -0.5,  -3.5, 0.0, 0.0, 1.0,
                     0.5, -0.5,  -4.5, 0.0, 0.0, 1.0,

                     0.5,  0.5,  -3.5, 0.0, 0.0, 1.0,
                     0.5, -0.5,  -4.5, 0.0, 0.0, 1.0,
                     0.5,  0.5,  -4.5, 0.0, 0.0, 1.0,
                    // Fourth face
                     0.5,  0.5,  -4.5, 1.0, 1.0, 0.0,
                     0.5, -0.5,  -4.5, 1.0, 1.0, 0.0,
                    -0.5, -0.5,  -4.5, 1.0, 1.0, 0.0,

                     0.5,  0.5,  -4.5, 1.0, 1.0, 0.0,
                    -0.5, -0.5,  -4.5, 1.0, 1.0, 0.0,
                    -0.5,  0.5,  -4.5, 1.0, 1.0, 0.0,
                    // Fifth face
                    -0.5, -0.5,  -4.5, 1.0, 0.0, 1.0,
                    -0.5,  0.5,  -3.5, 1.0, 0.0, 1.0,
                    -0.5, -0.5,  -3.5, 1.0, 0.0, 1.0,

                    -0.5,  0.5,  -3.5, 1.0, 0.0, 1.0,
                    -0.5,  0.5,  -4.5, 1.0, 0.0, 1.0,
                    -0.5, -0.5,  -4.5, 1.0, 0.0, 1.0,
                    // Sixth face
                     0.5, -0.5,  -3.5, 0.0, 1.0, 1.0,
                    -0.5,  0.5,  -3.5, 0.0, 1.0, 1.0,
                     0.5,  0.5,  -3.5, 0.0, 1.0, 1.0,

                     0.5, -0.5,  -3.5, 0.0, 1.0, 1.0,
                    -0.5, -0.5,  -3.5, 0.0, 1.0, 1.0,
                    -0.5,  0.5,  -3.5, 0.0, 1.0, 1.0,
                };

    glGenBuffers(1, &m_cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 216, m_cube, GL_STATIC_DRAW);


    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, m_triangle, GL_STATIC_DRAW);
    std::cout << sizeof(float) << std::endl;

//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
}

void GameRenderer::draw(GameContent*, QQuickWindow*)
{
    std::cout << "Draw " << std::endl;
    glUseProgram(m_programId);
    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO);

//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Perspective Matrix
    QMatrix4x4 perspective;
    perspective.setToIdentity();
    perspective.perspective(45, 800/600, 0.1, 100.0);
    glUniformMatrix4fv(glGetUniformLocation(m_programId, "perspective"), 1, GL_FALSE, perspective.data());

    QMatrix4x4 lookAt;
    lookAt.setToIdentity();
    lookAt.lookAt(QVector3D(4.0, 3.0, 3.0), QVector3D(0.0, 0.0, -4.0), QVector3D(0.0, 1.0, 0.0));
    glUniformMatrix4fv(glGetUniformLocation(m_programId, "lookAt"), 1, GL_FALSE, lookAt.data());


    glClearColor(0.2, 0.6, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glDrawArrays(GL_TRIANGLES, 0, 36);
    std::cout << "Draw End" << std::endl;
}



