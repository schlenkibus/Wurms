#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"


class GameWindow;

class GameScene {
public:
    explicit GameScene(GameWindow& parent);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    void onEvent(sf::Event& event);
protected:
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
    GameWindow& m_parent;
};
