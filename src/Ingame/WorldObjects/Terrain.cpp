//
// Created by justus on 24.08.18.
//

#include <SFML/Graphics/Sprite.hpp>
#include "Terrain.h"

Terrain::Terrain(b2World *m_world) //: m_terrainObject(m_world, createTerrainPolygons()) {
{
}

void Terrain::update(float delta) {

}

void Terrain::draw(sf::RenderWindow &window) {

}

bool Terrain::onEvent(sf::Event &e) {
    return false;
}

void Terrain::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}

std::vector<b2Vec2> Terrain::createTerrainPolygons() {
    auto ret = std::vector<b2Vec2>();

    return ret;
}
