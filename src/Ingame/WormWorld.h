#pragma once

#include <SFML/Window/Event.hpp>
#include "../GameObject.h"
#include "WorldObjects/Terrain.h"
#include "WorldObjects/Water.h"
#include "../UI/Overlay/PhysicsDebugger.h"

class IngameScene;

class WormWorld : public GameObject {
public:
    explicit WormWorld(IngameScene& parent);

    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;
    const PhysicsDebugger* getDebugger() const;
protected:
    b2World m_world;
    void onResize(sf::Event& resizeEvent) override;
    IngameScene& m_parent;
    Terrain m_terrain;
    //Water m_water;
    sf::View m_view;
    std::vector<std::unique_ptr<GameObject>> m_objects;
    PhysicsDebugger m_debugger;

    void moveCamera();

    bool handleZoom(sf::Event &event);

    float m_zoom = 1;
};