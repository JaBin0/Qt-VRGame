// Qt headers
#include <QQuickWindow>

// System headers
#include <iostream>

// Own headers
#include <Game.h>
#include <GameRenderer.h>
#include <GameContent.h>
#include <GameResourcesManager.h>

Game::Game()
    : m_renderer {nullptr}
    , m_content {nullptr}
    , m_resourcesManager {nullptr}
    , m_window {nullptr}
{
    connect(this, &QQuickItem::windowChanged, this, &Game::onWindowChanged);
}

Game::~Game() {
    std::cout << "Game::Destructor" << std::endl;
    delete m_resourcesManager;
    delete m_renderer;
    delete m_content;
}

void Game::init() {
    // Create game modules
    m_content = new GameContent();
    m_renderer = new GameRenderer();
    m_resourcesManager = new GameResourcesManager();

    // Initial modules
    m_renderer->init(m_resourcesManager, m_window);
    m_content->createScence();
    m_window->setClearBeforeRendering(false);
}

void Game::drawGame() {
    //std::cout << "Draw game frame" << std::endl;
    m_renderer->draw(m_content, m_window);

    m_window->update();
}

void Game::onWindowChanged(QQuickWindow *window) {
    m_window = window;
    if(nullptr != window) {
        connect(m_window, &QQuickWindow::sceneGraphInitialized, this, &Game::init, Qt::DirectConnection);
        connect(m_window, &QQuickWindow::beforeRendering, this, &Game::drawGame, Qt::DirectConnection);
        connect(m_window, &QQuickWindow::widthChanged, this, &Game::onWindowSizeChanged);
        connect(m_window, &QQuickWindow::heightChanged, this, &Game::onWindowSizeChanged);

    }
}

void Game::onWindowSizeChanged(int) {
    // Get current window size and adjust viewport
    QSize size = m_window->size();
    // TO DO - Adjust viewport
}
