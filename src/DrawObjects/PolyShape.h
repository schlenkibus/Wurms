#pragma once

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class PolyShape {
public:
    PolyShape(const std::vector<sf::Vector2f>& polygons);
    void draw(sf::RenderWindow& window);
protected:
    sf::ConvexShape m_shape;

    friend class TerrainObject;
};
