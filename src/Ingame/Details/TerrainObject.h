#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics/Texture.hpp>
#include "../../GameObject.h"
#include "../../DrawObjects/PolyShape.h"

class TerrainObject : public GameObject {
public:
    TerrainObject(b2World* world, const std::vector<b2Vec2>& polygons);
    void draw(sf::RenderWindow& window) override;
    bool onEvent(sf::Event& e) override;
    void update(float delta) override;

protected:
    void onResize(sf::Event& resizeEvent) override;

    PolyShape m_drawObject;

    std::vector<b2Vec2> m_polys;
    b2World* m_world;
    b2Body* m_body;
    b2FixtureDef m_fixtureDef;
    b2Fixture* m_fixture;
    b2BodyDef m_bodyDef;
    b2ChainShape m_shape;

    std::vector<sf::Vector2f> convertToSFMLCoords(const std::vector<b2Vec2>& vector);

    const float32 m_height = 2000;

    friend class Terrain;

    std::vector<b2Vec2> convertToBox2DCoords(const std::vector<b2Vec2> &vector);
};
