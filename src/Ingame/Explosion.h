#pragma once

#include "../GameObject.h"

class Terrain;
class b2World;

class Explosion : public GameObject {
public:
    Explosion(Terrain* terrain, b2World* world, sf::Vector2f pos);
    void draw(sf::RenderWindow& draw) override;
    void update(float delta) override;
    bool onEvent(sf::Event& event) override;
protected:
    void onResize(sf::Event& resizeEvent) override;
};
