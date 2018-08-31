#pragma once

#include "../../GameObject.h"

class Terrain : public GameObject {
enum Type {
    Land, Sky
};

public:
    Terrain();
    bool onEvent(sf::Event& e) override;
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;
protected:
    void onResize(sf::Event& resizeEvent) override;
    std::array<std::array<Type, 1000>, 500> m_tiles;
};