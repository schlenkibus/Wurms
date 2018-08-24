#include "GameWindow.h"

GameWindow::GameWindow(unsigned int w, unsigned int h) : m_window(sf::VideoMode(w, h), "Wurms", sf::Style::Close) {

}

int GameWindow::run() {

    static sf::Clock mainClock{};

    sf::Event e{};
    mainClock.restart();

    while(m_window.isOpen()) {
        while(m_window.pollEvent(e)) {
            if(e.type == sf::Event::Closed)
                m_window.close();
            m_scene->onEvent(e);
        }

        m_scene->update(mainClock.getElapsedTime().asSeconds());

        m_window.clear();
        m_scene->draw(m_window);
        m_window.display();
        mainClock.restart();
    }

    return 0;
}

const sf::Vector2i GameWindow::getMousePosition() const {
    auto pixPos =  sf::Mouse::getPosition(m_window);
    auto coordPos = m_window.mapPixelToCoords(pixPos);
    return sf::Vector2i(coordPos.x, coordPos.y);
}

const sf::Vector2i GameWindow::getMousePositionRelativeToWindow() const {
    return sf::Mouse::getPosition(m_window);
}

sf::RenderWindow &GameWindow::getRenderWindow() const {
    return const_cast<sf::RenderWindow&>(m_window);
}
