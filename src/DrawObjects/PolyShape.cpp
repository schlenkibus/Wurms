#include <SFML/Graphics/RenderWindow.hpp>
#include "PolyShape.h"

PolyShape::PolyShape(const std::vector<sf::Vector2f> &polygons) {
    m_shape.setPointCount(polygons.size() + 2);
    std::size_t index = 1;
    m_shape.setPoint(0, sf::Vector2f(0, 10000));
    for(auto& point: polygons) {
        m_shape.setPoint(index, point);
        index++;
    }
    m_shape.setPoint(polygons.size() + 1, sf::Vector2f(m_shape.getPoint(index-1).x + 1, 10000));
    m_shape.setOutlineColor(sf::Color::Green);
    m_shape.setFillColor(sf::Color::Cyan);
    m_shape.setOutlineThickness(1);
}

void PolyShape::draw(sf::RenderWindow &window) {
    window.draw(m_shape);
}
