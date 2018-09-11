#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include "../../../GameObject.h"


class ExplosionDebugObject : public GameObject {
public:
    ExplosionDebugObject(float radius);
    void draw(sf::RenderWindow& window) override;
    bool onEvent(sf::Event& e) override;
    void update(float delta) override;
protected:
    sf::CircleShape m_shape;
    bool m_active = false;
};
