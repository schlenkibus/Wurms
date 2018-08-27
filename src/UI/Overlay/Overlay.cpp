#include "Overlay.h"

void Overlay::update(float delta) {
    m_controls.update(delta);
}

bool Overlay::onEvent(sf::Event &e) {
    return m_controls.onEvent(e);
}

void Overlay::draw(sf::RenderWindow &window) {
    auto oldView = window.getView();
    window.setView(window.getDefaultView());
    m_controls.draw(window);
    window.setView(oldView);
}

void Overlay::addChild(GameObject *go) {
    m_controls.appendChild(go);
}
