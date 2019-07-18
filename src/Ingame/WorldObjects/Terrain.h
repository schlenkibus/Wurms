#pragma once

#include "../../GameObject.h"
#include "../Details/TerrainObject.h"
#include <Box2D/Box2D.h>

class Explosion;

class Terrain : public GameObject {

public:
    Terrain(b2World* world);
    bool onEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;
    void applyExplosion(Explosion* explo);
protected:
    b2World* m_world;
    std::vector<std::unique_ptr<TerrainObject>> m_terrainObjects;

    std::vector<b2Vec2> createTerrainPolygons();
};