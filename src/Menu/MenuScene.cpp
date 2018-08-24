//
// Created by justus on 24.08.18.
//

#include <iostream>
#include "MenuScene.h"
#include "../GameWindow.h"
#include "../UI/Label.h"
#include "../UI/GenericReactiveLabel.h"
#include "../UI/Button.h"

MenuScene::MenuScene(GameWindow& parent) : GameScene(parent) {
    m_gameObjects.push_back(std::make_unique<Label>(sf::Vector2f(300, 200), "Hello World!"));
    m_gameObjects.push_back(std::make_unique<GenericReactiveLabel>([](float delta, Label& l) {
        l.setText(std::string("frameTime:") + std::to_string(delta) + "s");
    }, sf::Vector2f(0, 0)));

    m_gameObjects.push_back(std::make_unique<Button>(sf::Vector2f(500, 200), "Clicked 0 Times!", [&](sf::Event& e, Button& b){
        static int counter = 0;
        if(e.type == sf::Event::MouseButtonReleased &&
           e.mouseButton.button == sf::Mouse::Left) {
            if(b.containsPosition(m_parent.getMousePosition()))
            {
                b.setText(std::string("Clicked ") + std::to_string(++counter) + " times");
                return true;
            }
        }
        return false;
    }, [](float delta, Button& b) {
        return;
    }));
}