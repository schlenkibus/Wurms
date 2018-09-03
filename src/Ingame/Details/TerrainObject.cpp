#include <memory>
#include <Box2D/Dynamics/b2Fixture.h>
#include <iostream>
#include "TerrainObject.h"
#include "../../UI/Overlay/PhysicsDebugger.h"
#include "../../Application.h"
#include "../../Tools/MathTools.h"

TerrainObject::TerrainObject(b2World* world, const std::vector<b2Vec2>& polygons) :
m_world(world), m_shape(), m_polys(convertToBox2DCoords(polygons)), m_drawObject(convertToSFMLCoords(polygons))
{
    sanitizePoints();
    calcObject();
}

void TerrainObject::draw(sf::RenderWindow &window) {
    m_drawObject.draw(window);
}

bool TerrainObject::onEvent(sf::Event &e) {
    return GameObject::onEvent(e);
}

void TerrainObject::update(float delta) {
    auto pos = m_body->GetTransform().p;
    m_drawObject.m_shape.setPosition(sf::Vector2f(pos.x, pos.y));
    m_drawObject.setRotation((int)(m_body->GetAngle()*180/M_1_PI) % 360);
}

void TerrainObject::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}

std::vector<sf::Vector2f> TerrainObject::convertToSFMLCoords(const std::vector<b2Vec2>& vector) {
    std::vector<sf::Vector2f> ret;
    ret.reserve(vector.size());

    for(auto& pos: vector) {
        ret.emplace_back(sf::Vector2f(pos.x, pos.y));
    }
    return ret;
}

std::vector<b2Vec2> TerrainObject::convertToBox2DCoords(const std::vector<b2Vec2> &vector) {
    std::vector<b2Vec2> ret;
    ret.reserve(vector.size());
    for(auto p: vector)
        ret.emplace_back(p);
    return ret;
}

bool contains(const sf::CircleShape* shape, float x, float y) {
    return shape->getRadius() >= MathTools::distance(shape->getPosition().x, shape->getPosition().y, x, y);
}

void TerrainObject::applyExplosion(Explosion *pExplosion) {

    sf::CircleShape clippingObject;
    clippingObject.setPosition(pExplosion->getPosition());
    clippingObject.setRadius(pExplosion->getRadius());
    clippingObject.setOrigin(clippingObject.getRadius() / 2, clippingObject.getRadius() / 2);

    std::vector<b2Vec2*> affectedPoints;

    for(auto& p: m_polys) {
        if(contains(&clippingObject, p.x, p.y)) {
            affectedPoints.emplace_back(&p);
        }
    }

    moveToOutsideOfCircle(&clippingObject, affectedPoints);

    sanitizePoints();

    calcObject();
    m_drawObject.calcObject(convertToSFMLCoords(m_polys));
}

void TerrainObject::calcObject() {
    if(m_fixture)
        m_body->DestroyFixture(m_fixture);

    if(m_body)
        m_world->DestroyBody(m_body);

    m_shape = std::make_unique<b2ChainShape>();

    auto height = m_drawObject.m_shape.getLocalBounds().height;
    m_bodyDef.type = b2_staticBody;
    m_body = m_world->CreateBody(&m_bodyDef);

    m_shape->CreateChain(&*m_polys.begin(), static_cast<int32>(m_polys.size()));
    m_fixtureDef.shape = m_shape.get();
    m_fixtureDef.density = 1;
    m_fixture = m_body->CreateFixture(&m_fixtureDef);
    auto po = m_body->GetTransform().p;
    m_drawObject.setPosition(sf::Vector2f(po.x, po.y));
}

void TerrainObject::moveToOutsideOfCircle(sf::CircleShape *pShape, std::vector<b2Vec2 *> vector) {

    for(auto* p: vector) {
        movePointToClosestCircleEdge(pShape->getPosition(), pShape->getRadius(), p);
    }
}

void TerrainObject::movePointToClosestCircleEdge(const sf::Vector2f &circleCenter, float radius, b2Vec2* pointToMove) {

    const auto A = circleCenter;
    const auto B = sf::Vector2f(pointToMove->x, pointToMove->y);
    const auto div = std::sqrt(std::pow(B.x - A.x, 2.f) + std::pow(B.y - A.y, 2.f));
    const auto cX = A.x + radius * (B.x - A.x) / div;
    const auto cY = A.y + radius * (B.y - A.y) / div;
    const auto closestPoint = sf::Vector2f(cX, cY);

    if(const auto* debugger = PhysicsDebugger::getDebugger()) {
        debugger->addExpiringPoint(B, sf::seconds(5));
        debugger->addExpiringPoint(circleCenter, sf::seconds(5));
        debugger->addExpiringPoint(closestPoint, sf::seconds(5));
    }

    if(MathTools::pnpoly(m_shape->m_count, m_shape->m_vertices, closestPoint.x, closestPoint.y) % 2 != 0) {
        pointToMove->x = closestPoint.x;
        pointToMove->y = closestPoint.y;
    } else {
        pointToMove->x = -99999;
        pointToMove->y = -99999;
    }

}

void TerrainObject::sanitizePoints() {

    auto count = m_polys.size();

    m_polys.begin()->Set(m_polys.begin()->x, -2000);
    m_polys.end()->Set(m_polys.end()->x, -2000);

    m_polys.erase(std::remove_if(m_polys.begin(), m_polys.end(), [](const b2Vec2& p){
        return p.x == -99999 && p.y == -99999;
    }), m_polys.end());

    std::cerr << "OUTSIDE OF SHAPE: removed: " << count - m_polys.size() << " verts!\n";
    count = m_polys.size();

    std::vector<int> indiciesToDelete;
    for(int i = 0; i < m_polys.size(); i++) {
        if(i > 0 && i + 1 < m_polys.size()) {
            if((int)b2DistanceSquared(m_polys[i-1], m_polys[i]) < 1 || (int)b2DistanceSquared(m_polys[i+1], m_polys[i]) < 1)
                indiciesToDelete.emplace_back(i);
        }
    }

    for(auto index: indiciesToDelete)
        m_polys.erase(m_polys.begin() + index);

    std::cerr << "TOO CLOSE: removed: " << count - m_polys.size() << " verts!\n";
}
