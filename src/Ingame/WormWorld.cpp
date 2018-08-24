#include <iostream>
#include "WormWorld.h"
#include "IngameScene.h"
#include "../Application.h"

WormWorld::WormWorld(IngameScene &parent) : m_parent(parent), m_terrain() {
    Application::get().getWindow().getRenderWindow().setView(m_view);
}

void WormWorld::update(float delta) {
    moveCamera();
}

bool WormWorld::onEvent(sf::Event &e) {
    if(e.type == sf::Event::KeyReleased) {
        if(handleZoom(e))
            return true;
    }
    return false;
}

void WormWorld::draw(sf::RenderWindow &window) {

}

void WormWorld::moveCamera() {
    static sf::Clock throttler;
    if(throttler.getElapsedTime().asSeconds() < 0.01)
        return;
    throttler.restart();

    auto& window = Application::get().getWindow().getRenderWindow();
    auto mousePos = Application::get().getWindow().getMousePositionRelativeToWindow();

    const bool rightBorder = mousePos.x > window.getSize().x - 50;
    const bool leftBorder = mousePos.x < 50;
    const bool topBorder = mousePos.y < 50;
    const bool bottomBorder = mousePos.y > window.getSize().y - 50;

    if(rightBorder)
        m_view.move(2, 0);
    if(leftBorder)
        m_view.move(-2, 0);
    if(topBorder)
        m_view.move(0, -2);
    if(bottomBorder)
        m_view.move(0, 2);

    window.setView(m_view);
}

bool WormWorld::handleZoom(sf::Event &event) {
    if(event.key.code == sf::Keyboard::PageDown) {
        m_view.zoom(2);
    } else if(event.key.code == sf::Keyboard::PageUp) {
        m_view.zoom(0.5f);
    } else {
        return false;
    }

    auto& window = Application::get().getWindow().getRenderWindow();
    window.setView(m_view);
    return true;
}
