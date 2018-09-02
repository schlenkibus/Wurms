#pragma once

#include "../GameObject.h"
#include "Details/SpriteParticleSystem.h"

class Terrain;
class b2World;

class Explosion : public GameObject {
public:
    Explosion(Terrain* terrain, b2World* world, sf::Vector2f pos);
    void draw(sf::RenderWindow& draw) override;
    void update(float delta) override;
    bool onEvent(sf::Event& event) override;
    bool finished() const;
protected:
    std::unique_ptr<SpriteParticleSystem> m_particleSystem;
};
