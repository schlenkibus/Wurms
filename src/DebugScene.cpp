#include <iostream>
#include "DebugScene.h"
#include "Tools/NoiseGenerator.h"
#include "UI/Label.h"

DebugScene::DebugScene(GameWindow &parent) : GameScene(parent) {
    int x = 0;
    for(auto y: NoiseGenerator::generateValues(187, 800, 600, 2, 2)) {
        std::cout << y << ',';
        m_gameObjects.push_back(std::make_unique<Label>(sf::Vector2f(x++, y), "."));
    }
}
