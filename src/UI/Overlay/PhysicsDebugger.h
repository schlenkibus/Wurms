#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Box2D/Dynamics/b2World.h>
#include "../../GameObject.h"

class PhysicsDebugger : public GameObject {
public:
    explicit PhysicsDebugger(b2World* world);
    void draw(sf::RenderWindow& window) override;
    bool onEvent(sf::Event& e) override;
    void update(float delta) override;
protected:
    void onResize(sf::Event& resizeEvent) override;
    b2World* m_world;

    void drawAllPoints(b2ChainShape *pShape, b2Body* body, sf::RenderWindow &renderWindow);
    void drawPoly(b2PolygonShape *pShape, b2Body* body, sf::RenderWindow &renderWindow);

    bool m_terrainRender = false;
    bool m_PolyRender = false;
};
