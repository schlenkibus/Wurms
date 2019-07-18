#include "DebugScene.h"
#include "Tools/NoiseGenerator.h"
#include "UI/Label.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

DebugScene::DebugScene(GameWindow &parent) : GameScene(parent), m_tree{Rect<float>(0, 0, 500, 500)} {
}

void DebugScene::onEvent(sf::Event &event) {
  if(event.type == sf::Event::MouseButtonPressed) {
    if(event.mouseButton.button == sf::Mouse::Left) {
      m_tree.insert(Point<float>(event.mouseButton.x, event.mouseButton.y));
    }
  }
  GameScene::onEvent(event);
}

void drawSubQuad(QuadTree<1>* tree, sf::RenderWindow& window) {
  if(tree) {
    sf::RectangleShape shape;
    auto rect = tree->getRect();
    //shape.setOrigin(rect.getWidth() / 2, rect.getHeigth() / 2);
    shape.setSize(sf::Vector2f(rect.getWidth(), rect.getHeigth()));
    shape.setPosition(rect.getX(), rect.getY());
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(0.5);
    shape.setOutlineColor(sf::Color::White);
    window.draw(shape);

    if(tree->isSubdivided()) {
      drawSubQuad(tree->getLT(), window);
      drawSubQuad(tree->getRT(), window);
      drawSubQuad(tree->getLB(), window);
      drawSubQuad(tree->getRB(), window);
    }
  }
}

void DebugScene::draw(sf::RenderWindow &window) {
  drawSubQuad(&m_tree, window);
}
