// Qt headers
#include <QQuickWindow>

// System headers
#include <iostream>

// Own headers
#include <GameRenderer.h>


GameRenderer::GameRenderer()
    : m_window(nullptr)
{
    std::cout << "GameRenderer::Constructor" << std::endl;
}

GameRenderer::~GameRenderer() {
    std::cout << "GameRenderer::Destructor" << std::endl;
}

const QQuickWindow* GameRenderer::window() {
    return m_window;
}

void GameRenderer::onWindowChanged(QQuickWindow *window) {
    // Set new window
    if(window != m_window) {
        // Clean previus connections
        disconnect(m_window, &QQuickWindow::widthChanged, this, &GameRenderer::onWindowSizeChanged);
        disconnect(m_window, &QQuickWindow::heightChanged, this, &GameRenderer::onWindowSizeChanged);

        // Set up new window callbacks
        m_window = window;
        if(nullptr != window) {
            connect(m_window, &QQuickWindow::widthChanged, this, &GameRenderer::onWindowSizeChanged);
            connect(m_window, &QQuickWindow::heightChanged, this, &GameRenderer::onWindowSizeChanged);
            connect(m_window, &QQuickWindow::beforeRendering, this, &GameRenderer::drawScene, Qt::DirectConnection);
        }
    }
}

void GameRenderer::onWindowSizeChanged()
{
    // Get current window size and adjust viewport
    QSize size = m_window->size();
    // TO DO - Adjust viewport
}

void GameRenderer::drawScene() {
    std::cout << "Render scene" << std::endl;
}
