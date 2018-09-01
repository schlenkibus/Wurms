#pragma once

#include <SFML/Graphics/ConvexShape.hpp>
#include "../../GameObject.h"

class Water : public GameObject {
public:
    Water();
    void draw(sf::RenderWindow& draw) override;
    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void setPosition(sf::Vector2f pos);
protected:
    void onResize(sf::Event& resizeEvent) override;
    sf::ConvexShape m_shape;

};
