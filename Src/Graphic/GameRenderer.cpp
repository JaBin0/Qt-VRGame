// Qt headers
#include <QGLWidget>
#include <QQuickWindow>
// System headers
#include <iostream>
// Own headers
#include <GameRenderer.h>

// Qt headers
//#include <QOpenGLContext>
//#include <QMatrix4x4>
//#include <QVector3D>
//#include <QVector>


// System headers
//#include <string.h>

// Own headers
//#include <Config.h>
//#include <SysMethods.h>
//#include <SystemTypes.h>
//#include <GameContent.h>
//#include <GameResourcesManager.h>

//#ifndef ANDROID
//    #define USE_ANDROID_SHADERS false
//#else
//    #define USE_ANDROID_SHADERS true
//#endif

// Static variablesSHADERS_CFG_DESKTOP
//const QString GameRenderer::SHADERS_CFG_ANDROID = ":/Android/ShadersCfg.cfg";
//const QString GameRenderer::SHADERS_CFG_DESKTOP = ":/Desktop/ShadersCfg.cfg";

GameRenderer::GameRenderer(QQuickWindow* window)
//    : m_perspective {}
//    , m_programId {0}
//    , m_triangle {nullptr}
//    , m_cubeVBO(0)
{
    // Set besic matrix to identity
    m_perspective.setToIdentity();

    // Initialize opengl context
    initializeOpenGLFunctions();
    setViewPort(window->size());

    // Enable basic opengl features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);

    std::cout << "GameRenderer::Constructor" << std::endl;
}

GameRenderer::~GameRenderer() {
    std::cout << "GameRenderer::Destructor" << std::endl;
}

void GameRenderer::createModel(ModelTemplate *modelTemp) {
    Model* model = new Model();
    model->trans = new QMatrix4x4(*modelTemp->trans);
    model->textureId = createTexture(modelTemp->image);
    model->vbo = createVBO(modelTemp->data);
    model->size = modelTemp->data->length() / 8;
    models.insert(modelTemp->id, model);
}

void GameRenderer::initShaders(QMap<QString, QPair<QString, QString> > *shaderSourcesMap) {
    for(auto key : shaderSourcesMap->keys()) {
        auto sources = shaderSourcesMap->value(key);
        uint err;
        shaders.insert(key, createGraphicPipline(sources.first, sources.second, err));
    }
}

void GameRenderer::renderFrame(QList<ContentPart *> *content) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    uint currentProgram = shaders.value("Basic");
    glUseProgram(currentProgram);

    // Perspective Matrix
    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "perspective"), 1, GL_FALSE, m_perspective.data());

    // Camera Matrix
    QMatrix4x4 lookAt;
    lookAt.setToIdentity();
    lookAt.lookAt(QVector3D(5.0, 5.0, 15.0), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0));
    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "lookAt"), 1, GL_FALSE, lookAt.data());

    for(auto obj : *content) {
        if(0 != models.count(obj->id)) {
            std::cout << "ID: " << obj->id.toUtf8().
                         constData() << std::endl;
            const Model* model = models.value(obj->id);
            glBindBuffer(GL_ARRAY_BUFFER, model->vbo);

            int pos = glGetAttribLocation(currentProgram, "vPos");
            int normal = glGetAttribLocation(currentProgram, "vNormal");
            int tex = glGetAttribLocation(currentProgram, "vText");
            glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(pos);

            glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(normal);

            glVertexAttribPointer(tex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(tex);

            // THIS IS HOW YOU ACTIVATE TEXTURE 0 !!!!! YOU STUPID BABUN
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, model->textureId);
            glUniform1i(glGetUniformLocation(currentProgram, "sampler"), 0);

            // Update uniforms
            // Transformation matrix external
            glUniformMatrix4fv(glGetUniformLocation(currentProgram, "transExt"), 1, GL_FALSE, obj->trans->data());

            // Update uniforms
            // Transformation matrix internal
            glUniformMatrix4fv(glGetUniformLocation(currentProgram, "transformInt"), 1, GL_FALSE, model->trans->data());

            glDrawArrays(GL_TRIANGLES, 0, model->size);
        }
    }
}

void GameRenderer::renderObject(QString modelName) {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Model* model = models.value(modelName);

    uint currentProgram = shaders.value("Basic");
    glUseProgram(currentProgram);
    glBindBuffer(GL_ARRAY_BUFFER, model->vbo);

    int pos = glGetAttribLocation(currentProgram, "vPos");
    int normal = glGetAttribLocation(currentProgram, "vNormal");
    int tex = glGetAttribLocation(currentProgram, "vText");
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(pos);

    glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(normal);

    glVertexAttribPointer(tex, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(tex);

//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(0);

//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//        glEnableVertexAttribArray(1);

//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//        glEnableVertexAttribArray(2);


    // THIS IS HOW YOU ACTIVATE TEXTURE 0 !!!!! YOU STUPID BABUN
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model->textureId);
    glUniform1i(glGetUniformLocation(currentProgram, "sampler"), 0);

    // Update uniforms
    // Transformation matrix
    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "transformInt"), 1, GL_FALSE, model->trans->data());

//    QMatrix4x4 trans;
//    trans.setToIdentity();
//    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "transformExt"), 1, GL_FALSE, trans.data());


    // Perspective Matrix
    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "perspective"), 1, GL_FALSE, m_perspective.data());

    // Camera Matrix
    QMatrix4x4 lookAt;
    lookAt.setToIdentity();
    lookAt.lookAt(QVector3D(5.0, 5.0, 15.0), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0));
    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "lookAt"), 1, GL_FALSE, lookAt.data());

    glDrawArrays(GL_TRIANGLES, 0, model->size);
}

void GameRenderer::renderUI() {
    static uint vbo = -1u;
    if(vbo == -1u) {
        QVector<float> data = {
            0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
        };

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * static_cast<uint>(data.length()), data.data(), GL_STATIC_DRAW);
    }

    QMatrix4x4 trans;
    trans.translate(1080.0f, 620.0f);
    trans.scale(200.0f, 100.0f);

    float* data = trans.data();
    for (auto idx = 0; idx < 16; ++idx) {
        std::cout << *(data+idx) << ", ";
    }
    std::cout << std::endl;


    glDisable(GL_DEPTH_TEST);
    uint currentProgram = shaders.value("Ortho");
    glUseProgram(currentProgram);

    // Perspective Matrix
    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "ort"), 1, GL_FALSE, m_ortho.data());
    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "transform"), 1, GL_FALSE, trans.data());

    int pos = glGetAttribLocation(currentProgram, "vPos");
    glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(pos);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
}

void GameRenderer::deleteModelTemplate(ModelTemplate *model) {
    delete model->data;
    delete model->trans;
    delete model;
}

//void GameRenderer::init(GameResourcesManager* const resMgrCallback, QQuickWindow* window) {

//    // Load Shaders
//    ShaderSourcMap shaderSrcMap;
//    uint err = 0;
//    if(USE_ANDROID_SHADERS) {
//        resMgrCallback->loadShaderSources(GameRenderer::SHADERS_CFG_ANDROID, shaderSrcMap);
//    }
//    else {
//        resMgrCallback->loadShaderSources(GameRenderer::SHADERS_CFG_DESKTOP, shaderSrcMap);
//    }

//    std::cout << "Creating graphic pipline programs ... ";
//    for (auto key : shaderSrcMap.keys()) {
//        QPair<QString, QString> pair = shaderSrcMap.value(key);
//        m_shadersMap.insert(key, createGraphicPipline(pair.first, pair.second, err));
//    }
//    SysMethods::errorCheck(err);

//}

//void GameRenderer::draw(GameContent* content, QQuickWindow*)
//{
//    uint currentProgram = m_shadersMap.value("Basic");
//    glUseProgram(currentProgram);
//    glBindBuffer(GL_ARRAY_BUFFER, m_cubeVBO);

//    // THIS IS HOW YOU ACTIVATE TEXTURE 0 !!!!! YOU STUPID BABUN
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, m_texture);
//    glUniform1i(glGetUniformLocation(currentProgram, "ourTexture"), 0);


//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);

//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);

//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);


//    // Perspective Matrix
//    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "perspective"), 1, GL_FALSE, m_perspective.data());

//    QMatrix4x4 lookAt;
//    lookAt.setToIdentity();
//    lookAt.lookAt(QVector3D(1.0, 2.0, 5.0), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0));
//    glUniformMatrix4fv(glGetUniformLocation(currentProgram, "lookAt"), 1, GL_FALSE, lookAt.data());

//    glClearColor(0.2, 0.2, 0.2, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glDrawArrays(GL_TRIANGLES, 0, m_size);
//}

void GameRenderer::setViewPort(QSize size) {
    glViewport(0, 0, size.width(), size.height());
    m_perspective.perspective(45, (double(size.width())/double(size.height())), 0.1, 1000.0);
    m_ortho.ortho(0.0f, 1280.0f, 0.0f, 720.0f, -100.0f, 100.f);
}

uint GameRenderer::createTexture(const QString textureName) {
    QImage img(":/Assets/Textures/" + textureName);
    img = QGLWidget::convertToGLFormat(img);
    //img = img.mirrored(true,false);
    uint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.height(), img.width(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
   // glGenerateMipmap(GL_TEXTURE_2D);

    return textureId;
}

uint GameRenderer::createVBO(QVector<float> *data) {
    uint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * static_cast<uint>(data->length()), data->data(), GL_STATIC_DRAW);
    return vbo;
}

uint GameRenderer::createGraphicPipline(const QString vertShaderSource, const QString fragShaderSource, uint& err) {
    int success = 0;
    char infoLog[512];
    std::cout << "vertShaderSource: \n" << vertShaderSource.toUtf8().constData() << std::endl;
    std::cout << "fragShaderSource: \n" << fragShaderSource.toUtf8().constData() << std::endl;
    // Create Vertex Shader
    const char* vertShaderSourceStart = vertShaderSource.toUtf8().constData();
    uint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertShaderSourceStart, nullptr);
    glCompileShader(vertexShaderId);

    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
        err = 1;
        std::cout << "ERROR::VERTEX::SHADER::COMPILE_FAILD\n" << infoLog << std::endl;
        glDeleteShader(vertexShaderId);
        return 0;
    }

    // Create Fragment Shader
    const char* fragShaderSourceStart = fragShaderSource.toUtf8().constData();
    uint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragShaderSourceStart, nullptr);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShaderId, 512, nullptr, infoLog);
        err = 2;
        std::cout << "ERROR::FRAGMENT::SHADER::COMPILE_FAILD\n" << infoLog << std::endl;
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
        return 0;
    }

    // Create graphic pipline program
    uint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(programId, 512, nullptr, infoLog);
        err = 3;
        std::cout << "ERROR::PROGRAM::LINKING_FAILD\n" << infoLog << std::endl;
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
        return 0;
    }

    //glDeleteShader(vertexShaderId);
    //glDeleteShader(fragmentShaderId);
    return programId;
}
