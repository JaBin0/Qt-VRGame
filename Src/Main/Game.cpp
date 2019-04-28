// Qt headers
#include <QQuickWindow>
// System headers
#include <iostream>
// Own headers
#include <Game.h>
#include <GameRenderer.h>
#include <GameRscManager.h>

// Static variables
const QString Game::LEVEL_FILE_PATH = ":/Assets/Levels/Scene.dae";

#ifndef ANDROID
    const QString Game::SHADERS_PATH = ":/Assets/Shaders/Desktop/ShadersCfg.cfg";
#else
    const QString Game::SHADERS_PATH = ":/Assets/Shaders/Android/ShadersCfg.cfg";
#endif

Game::Game()
    : m_rscManager {nullptr}
{
    connect(this, &QQuickItem::windowChanged, this, &Game::onWindowChanged);
}

Game::~Game() {
    delete m_rscManager;
}

void Game::onWindowChanged(QQuickWindow *window) {
    if(nullptr != window) {
        connect(window, &QQuickWindow::widthChanged, this, &Game::onWindowSizeChanged);
        connect(window, &QQuickWindow::heightChanged, this, &Game::onWindowSizeChanged);
        connect(window, &QQuickWindow::sceneGraphInitialized, this, &Game::init, Qt::DirectConnection);
        connect(window, &QQuickWindow::beforeRendering, this, &Game::drawFrame, Qt::DirectConnection);
    }
}

void Game::onWindowSizeChanged(int) {
    // In future adjast viewPort
    // window() <- return QSize of the connected window
}

void Game::init() {
    // Disable automatic clearing of openGL context so the content of the custom frame will be visible
    window()->setClearBeforeRendering(false);

    // Initialize all components
    m_rscManager = new GameRscManager();
    m_renderer = new GameRenderer(window());

    // Load content of the game
    RSC_ERROR err;
    ModelTemplate* modelTmp1 = m_rscManager->loadModel_Dae(":/Assets/Models/dae/Ground.dae", err);
    m_renderer->createModel(modelTmp1);
    m_renderer->deleteModelTemplate(modelTmp1);
    ModelTemplate* modelTmp2 = m_rscManager->loadModel_Dae(":/Assets/Models/dae/Cilinder.dae", err);
    m_renderer->createModel(modelTmp2);
    m_renderer->deleteModelTemplate(modelTmp2);
    ModelTemplate* modelTmp3 = m_rscManager->loadModel_Dae(":/Assets/Models/dae/Crate.dae", err);
    m_renderer->createModel(modelTmp3);
    m_renderer->deleteModelTemplate(modelTmp3);
    ModelTemplate* modelTmp4 = m_rscManager->loadModel_Dae(":/Assets/Models/dae/Piramid.dae", err);
    m_renderer->createModel(modelTmp4);
    m_renderer->deleteModelTemplate(modelTmp4);
    ModelTemplate* modelTmp5 = m_rscManager->loadModel_Dae(":/Assets/Models/dae/Sphere.dae", err);
    m_renderer->createModel(modelTmp5);
    m_renderer->deleteModelTemplate(modelTmp5);

    auto* shaderMap = m_rscManager->loadShaderSources(":/Assets/Shaders/Android/ShadersCfg.cfg");

    m_renderer->initShaders(shaderMap);
    std::cout << "hello" << std::endl;
    pContent = m_rscManager->load_Scene(LEVEL_FILE_PATH);
}

void Game::drawFrame() {
    m_renderer->renderFrame(pContent);
    //m_renderer->renderObject("Cone");
}
