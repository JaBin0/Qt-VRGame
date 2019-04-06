// Qt headers
#include <QQuickWindow>

// System headers
#include <iostream>

// Own headers
#include <Game.h>
#include <GameRenderer.h>
#include <GameContent.h>

Game::Game()
    : m_renderer {nullptr}
    , m_content {nullptr}
    , m_window {nullptr}
{
    connect(this, &QQuickItem::windowChanged, this, &Game::onWindowChanged);
}

Game::~Game() {
    std::cout << "Game::Destructor" << std::endl;
}

void Game::init() {
    // Create renderer module
    m_renderer = new GameRenderer();
    m_content = new GameContent();
    m_renderer->init();
    window()->setClearBeforeRendering(false);
}

void Game::drawGame() {
    std::cout << "Draw game frame" << std::endl;
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
