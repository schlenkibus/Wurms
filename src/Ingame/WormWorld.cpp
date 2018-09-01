#include <iostream>
#include "WormWorld.h"
#include "IngameScene.h"
#include "../Application.h"

WormWorld::WormWorld(IngameScene &parent) : m_parent(parent), m_terrain(nullptr) {
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


    sf::View view = Application::get().getWindow().getRenderWindow().getView();
    auto& window = Application::get().getWindow().getRenderWindow();
    auto mousePos = Application::get().getWindow().getMousePositionRelativeToWindow();

    const bool rightBorder = mousePos.x > window.getSize().x - 50;
    const bool leftBorder = mousePos.x < 50;
    const bool topBorder = mousePos.y < 50;
    const bool bottomBorder = mousePos.y > window.getSize().y - 50;

    if(rightBorder)
        view.move(2, 0);
    if(leftBorder)
        view.move(-2, 0);
    if(topBorder)
        view.move(0, -2);
    if(bottomBorder)
        view.move(0, 2);

    window.setView(view);
}

bool WormWorld::handleZoom(sf::Event &event) {
    sf::View view = Application::get().getWindow().getRenderWindow().getView();

    if(event.key.code == sf::Keyboard::PageDown) {
        view.zoom(2);
    } else if(event.key.code == sf::Keyboard::PageUp) {
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
