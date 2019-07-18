#pragma once
#include "GameScene.h"
#include "Tools/QuadTree.h"
#include <SFML/Graphics/RenderWindow.hpp>

class DebugScene : public GameScene {
public:
    DebugScene(GameWindow &parent);
    QuadTree<1> m_tree;
    void draw(sf::RenderWindow &window) override;
    void onEvent(sf::Event &event) override;
};
