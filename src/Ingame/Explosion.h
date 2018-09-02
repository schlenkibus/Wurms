#pragma once

#include <Box2D/Common/b2Math.h>
#include "../GameObject.h"
#include "Details/SpriteParticleSystem.h"

class Terrain;
class TerrainObject;
class b2World;
class b2Body;

class Explosion : public GameObject {
public:
    Explosion(Terrain* terrain, b2World* world, sf::Vector2f pos, float radius = 100.f);
    void draw(sf::RenderWindow& draw) override;
    void update(float delta) override;
    bool onEvent(sf::Event& event) override;
    bool finished() const;
    sf::Vector2f getPosition();
    float getRadius();

protected:
    std::unique_ptr<SpriteParticleSystem> m_particleSystem;
    sf::Vector2f m_position;
    float m_radius;

    b2Vec2 createForceInDirection(b2Body* body, float strength) const;
    std::vector<b2Body*> getBodysInRadius(sf::Vector2f position, b2World *pWorld, float radius);

    friend class TerainObject;
};
