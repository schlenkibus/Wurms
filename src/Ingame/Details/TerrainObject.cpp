#include <Box2D/Dynamics/b2Fixture.h>
#include "TerrainObject.h"

TerrainObject::TerrainObject(b2World* world, const std::vector<b2Vec2>& polygons) :
m_world(world), m_shape(), m_polys(polygons)
{
    //m_bodyDef.type = b2_staticBody;
    //m_shape.Set(&*polygons.begin(), static_cast<int32>(m_polys.size()));
    //m_body = world->CreateBody(&m_bodyDef);
    //m_fixture = m_body->CreateFixture(&m_shape, 20);
}

void TerrainObject::draw(sf::RenderWindow &window) {

}

bool TerrainObject::onEvent(sf::Event &e) {
    return GameObject::onEvent(e);
}

void TerrainObject::update(float delta) {

}
