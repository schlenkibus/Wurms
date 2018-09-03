#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Box2D/Dynamics/b2World.h>
#include <SFML/Graphics/CircleShape.hpp>
#include "../../GameObject.h"

class PhysicsDebugger : public GameObject {
public:
    explicit PhysicsDebugger(b2World* world);
    void draw(sf::RenderWindow& window) override;
    bool onEvent(sf::Event& e) override;
    void update(float delta) override;

    static const PhysicsDebugger *getDebugger();

    void addExpiringPoint(sf::Vector2<float> position, sf::Time time) const; //more like mutable

protected:
    void onResize(sf::Event& resizeEvent) override;
    b2World* m_world;

    void drawAllPoints(b2ChainShape *pShape, b2Body* body, sf::RenderWindow &renderWindow);
    void drawPoly(b2PolygonShape *pShape, b2Body* body, sf::RenderWindow &renderWindow);

    bool m_terrainRender = false;
    bool m_PolyRender = false;
    mutable std::vector<std::pair<sf::CircleShape, sf::Time>> m_expiringPoints;
};
