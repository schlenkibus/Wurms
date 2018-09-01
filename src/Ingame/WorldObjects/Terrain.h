#pragma once

#include "../../GameObject.h"
#include "../Details/TerrainObject.h"
#include <Box2D/Box2D.h>

class Terrain : public GameObject {

public:
    Terrain(b2World* m_world);
    bool onEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;
protected:
//    TerrainObject m_terrainObject;
    void onResize(sf::Event& resizeEvent) override;

    std::vector<b2Vec2> createTerrainPolygons();
};