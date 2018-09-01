#include <iostream>
#include "WormWorld.h"
#include "IngameScene.h"
#include "../Application.h"

WormWorld::WormWorld(IngameScene &parent) : m_parent(parent), m_terrain(&m_world) {
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
    m_terrain.draw(window);
}

void WormWorld::moveCamera() {
    static sf::Clock throttler;
    if(throttler.getElapsedTime().asSeconds() < 0.01)
        return;
    throttler.restart();


    sf::View view = Application::get().getWindow().getRenderWindow().getView();
    auto& window = Application::get().getWindow().getRenderWindow();
    auto mousePos = Application::get().getWindow().getMousePositionRelativeToWindow();

    const bool rightBorder = mousePos.x > window.getSize().x - 50;
    const bool leftBorder = mousePos.x < 50;
    const bool topBorder = mousePos.y < 50;
    const bool bottomBorder = mousePos.y > window.getSize().y - 50;

    auto moveFactor = 2 * m_zoom;

    if(rightBorder)
        view.move(moveFactor, 0);
    if(leftBorder)
        view.move(-moveFactor, 0);
    if(topBorder)
        view.move(0, -moveFactor);
    if(bottomBorder)
        view.move(0, moveFactor);

    window.setView(view);
}

bool WormWorld::handleZoom(sf::Event &event) {
    sf::View view = Application::get().getWindow().getRenderWindow().getView();

    if(event.key.code == sf::Keyboard::PageDown) {
        m_zoom *= 2;
        view.zoom(2);
    } else if(event.key.code == sf::Keyboard::PageUp) {
        m_zoom *= 0.5;
        view.zoom(0.5f);
    } else {
        return false;
    }

    auto& window = Application::get().getWindow().getRenderWindow();
    window.setView(view);
    return true;
}

void WormWorld::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}
