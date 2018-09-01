#pragma once

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "../../GameObject.h"

class TerrainObject : public GameObject {
public:
    TerrainObject(b2World* world, const std::vector<b2Vec2>& polygons);
    void draw(sf::RenderWindow& window) override;
    bool onEvent(sf::Event& e) override;
    void update(float delta) override;
protected:
    const std::vector<b2Vec2> m_polys;
    b2World* m_world;
    b2Body* m_body;
    b2PolygonShape m_shape;
};
