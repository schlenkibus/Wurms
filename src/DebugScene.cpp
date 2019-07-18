#include "DebugScene.h"
#include "Ingame/QuadTreeTerrain/QuadTreeTerrain.h"
#include "Tools/NoiseGenerator.h"
#include "UI/Label.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

DebugScene::DebugScene(GameWindow &parent) : GameScene(parent) {
  m_gameObjects.emplace_back(std::make_unique<QuadTreeTerrain>());
}

void drawSubQuad(QuadTree<1>* tree, sf::RenderWindow& window) {
  if(tree) {
    sf::RectangleShape shape;
    auto rect = tree->getRect();
    //shape.setOrigin(rect.getWidth() / 2, rect.getHeigth() / 2);
    shape.setSize(sf::Vector2f(rect.getWidth(), rect.getHeigth()));
    shape.setPosition(rect.getX(), rect.getY());
    shape.setFillColor(tree->m_color);
    //shape.setOutlineThickness(0.5);
    //shape.setOutlineColor(sf::Color::Black);
    window.draw(shape);

    if(tree->isSubdivided()) {
      drawSubQuad(tree->getLT(), window);
      drawSubQuad(tree->getRT(), window);
      drawSubQuad(tree->getLB(), window);
      drawSubQuad(tree->getRB(), window);
    }
  }
}