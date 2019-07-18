#include "QuadTreeTerrain.h"
#include "../Explosion.h"
#include <SFML/Graphics/RectangleShape.hpp>

QuadTreeTerrain::QuadTreeTerrain() : m_tree{Rect<float>(0, 300, 1000, 1000)} {
  m_tree.subdivide();
  m_tree.traverse([](QuadTree<1>& node){
    node.subdivide();
    return false;
  });
}

void drawSubQuad(QuadTree<1>*, sf::RenderWindow&);

void QuadTreeTerrain::draw(sf::RenderWindow &window) {
  drawSubQuad(&m_tree, window);
}

void QuadTreeTerrain::update(float deltaTime) {

}
bool QuadTreeTerrain::onEvent(sf::Event &event) {
  if(event.type == sf::Event::MouseButtonPressed) {
    if(event.mouseButton.button == sf::Mouse::Left) {
      const auto radius = 50;

      for(auto y = event.mouseButton.y - radius; y <= event.mouseButton.y + radius; y++) {
        for(auto x = event.mouseButton.x - radius;x <= event.mouseButton.x + radius; x++) {
          auto distance = std::sqrt(std::pow(x - event.mouseButton.x, 2) + std::pow(y - event.mouseButton.y, 2));
          if(distance <= radius + 1.5 && distance >= radius - 1.5) {
            m_tree.insert(Point<float>(x, y));
          }
        }
      }

      std::vector<QuadTree<1>*> insideExplosion;
      m_tree.traverse([&insideExplosion, event, radius](QuadTree<1>& node) {
        if(node.getRect().intersectsCircle(event.mouseButton.x, event.mouseButton.y, radius)) {
          insideExplosion.emplace_back(&node);
          return true;
        }
        return false;
      });

      for(auto& q: insideExplosion) {
        q->m_color = sf::Color::Transparent;
      }
    }
  }
  return GameObject::onEvent(event);
}
