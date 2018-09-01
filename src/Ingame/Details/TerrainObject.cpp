#include <Box2D/Dynamics/b2Fixture.h>
#include "TerrainObject.h"
#include "../../Application.h"

TerrainObject::TerrainObject(b2World* world, const std::vector<b2Vec2>& polygons) :
m_world(world), m_shape(), m_polys(polygons), m_drawObject(convertToSFMLCoords(polygons))
{

}

void TerrainObject::draw(sf::RenderWindow &window) {
    m_drawObject.draw(window);
}

bool TerrainObject::onEvent(sf::Event &e) {
    return GameObject::onEvent(e);
}

void TerrainObject::update(float delta) {

}

void TerrainObject::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}

std::vector<sf::Vector2f> TerrainObject::convertToSFMLCoords(const std::vector<b2Vec2> vector) {
    std::vector<sf::Vector2f> ret;
    ret.reserve(vector.size());

    for(auto& pos: vector) {
        ret.emplace_back(sf::Vector2f(pos.x, pos.y));
    }
    return ret;
}
