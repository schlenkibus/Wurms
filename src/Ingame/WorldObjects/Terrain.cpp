#include <SFML/Graphics/Sprite.hpp>
#include "Terrain.h"
#include "../../Tools/NoiseGenerator.h"
#include "../Explosion.h"

Terrain::Terrain(b2World *world) : m_world(world) {
    m_terrainObjects.emplace_back(std::make_unique<TerrainObject>(world, createTerrainPolygons()));
}

void Terrain::update(float delta) {
    for(auto& terrain: m_terrainObjects) {
        terrain->update(delta);
    }
}

void Terrain::draw(sf::RenderWindow &window) {
    for(auto& terrain: m_terrainObjects) {
        terrain->draw(window);
    }
}

bool Terrain::onEvent(sf::Event &e) {
    for(auto& terrain: m_terrainObjects) {
        if(terrain->onEvent(e))
            return true;
    }
    return false;
}

std::vector<b2Vec2> Terrain::createTerrainPolygons() {
    std::vector<b2Vec2> ret;

    const auto minSize = std::size_t(500);
    auto unNormalizedNoise = NoiseGenerator::generateValues(1870, 1000, 600, 3, 4);
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

void Terrain::addTerrainObject(std::vector<b2Vec2> polys) {
    m_terrainObjects.emplace_back();
}

void Terrain::applyExplosion(Explosion *explo) {
    for(auto& terrain: m_terrainObjects) {
        terrain->applyExplosion(explo);
    }

    m_terrainObjects.erase(std::find_if(m_terrainObjects.begin(), m_terrainObjects.end(), [](std::unique_ptr<TerrainObject>& obj) {
        return obj->getPolyCount() <= 0;
    }), m_terrainObjects.end());
}
