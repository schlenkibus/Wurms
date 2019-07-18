#pragma once
#include "PushArray.h"
#include "Rect.h"
#include <SFML/Graphics/Color.hpp>
#include <cstdio>
#include <functional>
#include <memory>
#include <vector>

template<size_t capacity>
class QuadTree {
public:
    using tTraverseCB = std::function<bool(QuadTree<capacity> &)>;

    explicit QuadTree(const Rect<float>& rect);
    bool insert(Point<float> pos);
    QuadTree<capacity>* getLT();
    QuadTree<capacity>* getRT();
    QuadTree<capacity>* getLB();
    QuadTree<capacity>* getRB();
    const PushArray<Point<float>, capacity>& getData() const;
    const Rect<float>& getRect() const;
    const bool isSubdivided() const;
    void traverse(tTraverseCB cb);
    sf::Color m_color = sf::Color::Green;
    void subdivide();
protected:

    std::unique_ptr<QuadTree<capacity>> m_leftTop;
    std::unique_ptr<QuadTree<capacity>> m_rightTop;
    std::unique_ptr<QuadTree<capacity>> m_leftBottom;
    std::unique_ptr<QuadTree<capacity>> m_rightBottom;
    std::vector<Point<float>> m_items;
    Rect<float> m_rect;
    bool m_subdivided = false;
};

template <size_t capacity>
QuadTree<capacity>::QuadTree(const Rect<float> &rect) : m_rect{rect}, m_items{} {

}

static const int s_sizeThreshold = 50;

template <size_t capacity> bool QuadTree<capacity>::insert(Point<float> pos) {
    if(!m_rect.contains(pos)) {
        return false;
    }

    if(m_items.size() >= capacity) {
        if(!m_subdivided) {
            subdivide();
        }
        if(m_leftTop->insert(pos))
          return true;
        if(m_rightTop->insert(pos))
          return true;
        if(m_leftBottom->insert(pos))
          return true;
        if(m_rightBottom->insert(pos))
          return true;
    } else {
        m_items.emplace_back(pos);
        return true;
    }
    return false;
}

template <size_t capacity> void QuadTree<capacity>::subdivide() {
    const auto x = m_rect.getX();
    const auto y = m_rect.getY();
    const auto w = m_rect.getWidth();
    const auto h = m_rect.getHeigth();

    const auto lt = Rect<float>(x , y, w / 2, h / 2);
    m_leftTop = std::make_unique<QuadTree<capacity>>(lt);
    m_leftTop->m_color = m_color;
    const auto rt = Rect<float>(x + w / 2, y, w / 2, h / 2);
    m_rightTop = std::make_unique<QuadTree<capacity>>(rt);
    m_rightTop->m_color = m_color;
    const auto lb = Rect<float>(x, y + h / 2, w / 2, h / 2);
    m_leftBottom = std::make_unique<QuadTree<capacity>>(lb);
    m_leftBottom->m_color = m_color;
    const auto rb = Rect<float>(x + w / 2, y + h / 2, w / 2, h / 2);
    m_rightBottom = std::make_unique<QuadTree<capacity>>(rb);
    m_rightBottom->m_color = m_color;

    m_subdivided = true;
}
template <size_t capacity> QuadTree<capacity> *QuadTree<capacity>::getLT() {
  return m_leftTop.get();
}
template <size_t capacity> QuadTree<capacity> *QuadTree<capacity>::getRT() {
  return m_rightTop.get();
}
template <size_t capacity> QuadTree<capacity> *QuadTree<capacity>::getLB() {
  return m_leftBottom.get();
}
template <size_t capacity> QuadTree<capacity> *QuadTree<capacity>::getRB() {
  return m_rightBottom.get();
}
template <size_t capacity>
const PushArray<Point<float>, capacity> &QuadTree<capacity>::getData() const {
  return m_items;
}
template <size_t capacity>
const Rect<float> &QuadTree<capacity>::getRect() const {
  return m_rect;
}
template <size_t capacity> const bool QuadTree<capacity>::isSubdivided() const {
  return m_subdivided;
}
template <size_t capacity>
void QuadTree<capacity>::traverse(tTraverseCB cb) {
  if(cb(*this)) {
    if(m_leftTop)
      m_leftTop->traverse(cb);
    if(m_rightTop)
      m_rightTop->traverse(cb);
    if(m_leftBottom)
      m_leftBottom->traverse(cb);
    if(m_rightBottom)
      m_rightBottom->traverse(cb);
  }
}
