#include <SFML/Graphics/Sprite.hpp>
#include "Terrain.h"
#include "../../Tools/NoiseGenerator.h"
#include "../Explosion.h"

Terrain::Terrain(b2World *world) : m_terrainObject(world, createTerrainPolygons()) {

}

void Terrain::update(float delta) {
    m_terrainObject.update(delta);
}

void Terrain::draw(sf::RenderWindow &window) {
    m_terrainObject.draw(window);
}

bool Terrain::onEvent(sf::Event &e) {
    return m_terrainObject.onEvent(e);
}

void Terrain::onResize(sf::Event &resizeEvent) {
    m_terrainObject.onResize(resizeEvent);
}

std::vector<b2Vec2> Terrain::createTerrainPolygons() {
    std::vector<b2Vec2> ret;

    const auto minSize = std::size_t(5000);
    auto unNormalizedNoise = NoiseGenerator::generateValues(187, 8000, 600, 3, 4);
    auto firstPoint = *unNormalizedNoise.begin();

    int x = 0;
    for(auto y: unNormalizedNoise) {
        if(y == firstPoint && ret.size() >= minSize)
            break;

        ret.emplace_back(b2Vec2(x, y));
        x++;
    }

    return ret;
}

void Terrain::applyExplosion(Explosion *explo) {
    m_terrainObject.applyExplosion(explo);
}
