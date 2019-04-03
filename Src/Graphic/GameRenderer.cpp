// Qt headers
#include <QQuickWindow>

// System headers
#include <iostream>
#include <string.h>

// Own headers
#include <GameRenderer.h>
#include <GameContent.h>

GameRenderer::GameRenderer()
    : m_programId {0}
    , m_triangle {nullptr}
{
    initializeOpenGLFunctions();
}

GameRenderer::~GameRenderer() {
    std::cout << "GameRenderer::Destructor" << std::endl;
}

void GameRenderer::init() {

    const char* vertexShaderSource = "attribute vec2 vPos;\n"
                                     "void main() {\n"
                                     "    gl_Position = vec4(vPos, 0.0, 1.0);\n"
                                     "}\0";

    const char* fragmentShaderSource = "void main() {\n"
                                       "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
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


}

void GameRenderer::draw(GameContent *content)
{

}



