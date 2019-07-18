#pragma once
#include "../../GameObject.h"
#include "../../Tools/QuadTree.h"
#include <SFML/Graphics/RenderWindow.hpp>

class QuadTreeTerrain : public GameObject {
public:
  QuadTreeTerrain();
  bool onEvent(sf::Event &event) override;
  void draw(sf::RenderWindow &window) override;
  void update(float deltaTime) override;
protected:
  QuadTree<1> m_tree;
};