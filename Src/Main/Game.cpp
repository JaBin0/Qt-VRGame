// Qt headers
#include <QQuickWindow>

// System headers
#include <iostream>

// Own headers
#include <Game.h>
#include <GameRenderer.h>

Game::Game()
    : m_renderer(new GameRenderer())
{
    std::cout << "Game::Constructor" << std::endl;
    connect(this, &QQuickItem::windowChanged, m_renderer, &GameRenderer::onWindowChanged);

}

Game::~Game() {
    std::cout << "Game::Destructor" << std::endl;
}

void Game::test()
{
    std::cout << "before synchronizinig" << std::endl;
}

void Game::handleWindowChanged(QQuickWindow *window)
{
    std::cout << window->width() << std::endl;
    connect(window, &QQuickWindow::beforeSynchronizing, this, &Game::test, Qt::DirectConnection);
}
