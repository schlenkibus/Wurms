#include <Box2D/Dynamics/b2Fixture.h>
#include "TerrainObject.h"
#include "../../Application.h"

TerrainObject::TerrainObject(b2World* world, const std::vector<b2Vec2>& polygons) :
m_world(world), m_shape(), m_polys(convertToBox2DCoords(polygons)), m_drawObject(convertToSFMLCoords(polygons))
{
    auto height = m_drawObject.m_shape.getLocalBounds().height;
    m_bodyDef.type = b2_staticBody;
    m_body = world->CreateBody(&m_bodyDef);
    m_polys.begin()->Set(m_polys.begin()->x, -2000);
    m_polys.end()->Set(m_polys.end()->x, -2000);

    m_shape.CreateLoop(&*m_polys.begin(), static_cast<int32>(polygons.size()));
    m_fixtureDef.shape = &m_shape;
    m_fixtureDef.density = 1;
    m_fixture = m_body->CreateFixture(&m_fixtureDef);
    auto po = m_body->GetTransform().p;
    m_drawObject.setPosition(sf::Vector2f(po.x, po.y));
    m_drawObject.setRotation((int)(m_body->GetAngle()*180/M_1_PI) % 360);
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
