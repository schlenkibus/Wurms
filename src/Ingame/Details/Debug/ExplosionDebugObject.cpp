//
// Created by justus on 07.09.18.
//

#include "ExplosionDebugObject.h"
#include "../../../Application.h"

ExplosionDebugObject::ExplosionDebugObject(float radius) {
    m_shape.setRadius(radius);
    m_shape.setOrigin(radius, radius);
}

void ExplosionDebugObject::draw(sf::RenderWindow &window) {
    if(m_active)
        window.draw(m_shape);
}

bool ExplosionDebugObject::onEvent(sf::Event &e) {
    if(e.type == sf::Event::KeyReleased) {
        switch(e.key.code) {
            case sf::Keyboard::E:
                m_active = !m_active;
                break;
            default:
                break;
        }
    }

    return GameObject::onEvent(e);
}

void ExplosionDebugObject::update(float delta) {
    auto pos = Application::get().getWindow().getMousePosition();
    m_shape.setPosition(pos.x, pos.y);
}
