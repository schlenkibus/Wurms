#pragma once

#include <SFML/Window/Event.hpp>
#include "../GameObject.h"
#include "WorldObjects/Terrain.h"

class IngameScene;

class WormWorld : public GameObject {
public:
    explicit WormWorld(IngameScene& parent);

    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;
protected:
    void onResize(sf::Event& resizeEvent) override;
    IngameScene& m_parent;
    Terrain m_terrain;
    sf::View m_view;

    void moveCamera();

    bool handleZoom(sf::Event &event);
};