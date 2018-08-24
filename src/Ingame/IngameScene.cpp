#include "IngameScene.h"
#include "../UI/Label.h"
#include "WormWorld.h"
#include "../UI/Button.h"
#include "Details/ParticleSystem.h"
#include "../UI/GenericReactiveLabel.h"

IngameScene::IngameScene(GameWindow& parent) : GameScene(parent) {
    m_gameObjects.push_back(std::make_unique<Label>(sf::Vector2f(0,0), "Ingame!"));
    m_gameObjects.push_back(std::make_unique<Button>(sf::Vector2f(100, 100), "BUTTON!", nullptr, nullptr));
    m_gameObjects.push_back(std::make_unique<ParticleSystem>());
    m_gameObjects.push_back(std::make_unique<WormWorld>(*this));
    m_gameObjects.push_back(std::make_unique<GenericReactiveLabel>([](float delta, Label& l) {
        l.setText(std::string("frameTime:") + std::to_string(delta) + "s");
    }, sf::Vector2f(0, 0)));
}
