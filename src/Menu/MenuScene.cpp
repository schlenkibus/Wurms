#include <iostream>
#include "MenuScene.h"
#include "../GameWindow.h"
#include "../UI/Label.h"
#include "../UI/GenericReactiveLabel.h"
#include "../UI/Button.h"
#include "../Ingame/IngameScene.h"

MenuScene::MenuScene(GameWindow& parent) : GameScene(parent) {
    m_gameObjects.push_back(std::make_unique<Label>(sf::Vector2f(300, 200), "Wurms! V0.0.1"));
    m_gameObjects.push_back(std::make_unique<GenericReactiveLabel>([](float delta, Label& l) {
        l.setText(std::string("frameTime:") + std::to_string(delta) + "s");
    }, sf::Vector2f(0, 0)));

    m_gameObjects.push_back(std::make_unique<Button>(sf::Vector2f(300, 450), "Quit!", [&](sf::Event& e, Button& b){
        static int counter = 0;
        if(e.type == sf::Event::MouseButtonReleased &&
           e.mouseButton.button == sf::Mouse::Left) {
            if(b.containsPosition(m_parent.getMousePosition()))
            {
                m_parent.getRenderWindow().close();
               return true;
            }
        }
        return false;
    }, nullptr));

    m_gameObjects.push_back(std::make_unique<Button>(sf::Vector2f(300, 350), "Play", [&](sf::Event& e, Button& b){
        static int counter = 0;
        if(e.type == sf::Event::MouseButtonReleased &&
           e.mouseButton.button == sf::Mouse::Left) {
            if(b.containsPosition(m_parent.getMousePosition()))
            {
                m_parent.setScene<IngameScene>();
                return true;
            }
        }
        return false;
    }, nullptr));
}