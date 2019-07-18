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

}


void Terrain::applyExplosion(Explosion *explo) {

}
