#include <SFML/Graphics/RenderWindow.hpp>
#include "Water.h"
#include "../../Tools/NoiseGenerator.h"
#include "../../Tools/ResourceManager.h"

Water::Water() {
    auto waterPoints = NoiseGenerator::generateWater(10000);
    m_shape.setPointCount(waterPoints.size() + 2);
    std::size_t index = 1;
    m_shape.setPoint(0, sf::Vector2f(0, 1000));
    for(auto& point: waterPoints) {
        m_shape.setPoint(index, sf::Vector2f(index, point));
        index++;
    }
    m_shape.setPoint(waterPoints.size() + 1, sf::Vector2f(m_shape.getPoint(index-1).x + 1, 1000));
    m_shape.setTexture(&ResourceManager::get().getTexture("/water.png"));
    ResourceManager::get().getTexture("/water.png").setRepeated(true);
    m_shape.setTextureRect(sf::IntRect(0, 0, static_cast<int>(m_shape.getLocalBounds().width),
                                       static_cast<int>(m_shape.getLocalBounds().height)));
}

void Water::draw(sf::RenderWindow &draw) {
    draw.draw(m_shape);
}

void Water::update(float delta) {

}

bool Water::onEvent(sf::Event &e) {
    return GameObject::onEvent(e);
}

void Water::setPosition(sf::Vector2f pos) {
    m_shape.setPosition(pos);
}

void Water::onResize(sf::Event &resizeEvent) {

}
