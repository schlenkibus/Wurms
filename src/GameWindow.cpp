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
    return sf::Mouse::getPosition(m_window);
}
