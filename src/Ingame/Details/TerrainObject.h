#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics/Texture.hpp>
#include "../../GameObject.h"
#include "../../DrawObjects/PolyShape.h"
#include "../Explosion.h"

class TerrainObject : public GameObject {
public:
    TerrainObject(b2World* world, const std::vector<b2Vec2>& polygons);
    void draw(sf::RenderWindow& window) override;
    bool onEvent(sf::Event& e) override;
    void update(float delta) override;
    const size_t getPolyCount() const;

protected:
    void calcObject();
    void onResize(sf::Event& resizeEvent) override;

    std::vector<b2Vec2> m_polys;

    PolyShape m_drawObject;
    b2World* m_world = nullptr;
    b2Body* m_body = nullptr;
    b2FixtureDef m_fixtureDef;
    b2Fixture* m_fixture = nullptr;
    b2BodyDef m_bodyDef;
    std::unique_ptr<b2ChainShape> m_shape;

    std::vector<sf::Vector2f> convertToSFMLCoords(const std::vector<b2Vec2>& vector);

    friend class Terrain;

    std::vector<b2Vec2> convertToBox2DCoords(const std::vector<b2Vec2> &vector);

    void applyExplosion(Explosion *pExplosion);

    std::vector<b2Vec2*> calculateAffectedPoints(sf::CircleShape& shape);
    void moveToOutsideOfCircle(sf::CircleShape *pShape, std::vector<b2Vec2 *> vector);
    void movePointToClosestCircleEdge(const sf::Vector2f &circleCenter, float radius, b2Vec2* pointToMove);
    void doSplit(sf::CircleShape& shape, std::vector<b2Vec2*> affectedPoints);
    void sanitizePoints();

    bool doesExplosionBreakCircle(std::vector<b2Vec2 *> &affectedPoints);
};
