#pragma once
#include "PushArray.h"
#include "Rect.h"
#include <vector>
#include <cstdio>
#include <memory>

template<size_t capacity>
class QuadTree {
public:
    explicit QuadTree(const Rect<float>& rect);
    void insert(Point<float> pos);
    QuadTree<capacity>* getLT();
    QuadTree<capacity>* getRT();
    QuadTree<capacity>* getLB();
    QuadTree<capacity>* getRB();
    const PushArray<Point<float>, capacity>& getData() const;
    const Rect<float>& getRect() const;
    const bool isSubdivided() const;
protected:
    void subdivide();

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

template <size_t capacity>
void QuadTree<capacity>::insert(Point<float> pos) {
    if(!m_rect.contains(pos)) {
        return;
    }

    if(m_items.size() >= capacity) {
        if(!m_subdivided) {
            subdivide();
        }
        m_leftTop->insert(pos);
        m_rightTop->insert(pos);
        m_leftBottom->insert(pos);
        m_rightBottom->insert(pos);
    } else {
        m_items.emplace_back(pos);
    }
}

template <size_t capacity> void QuadTree<capacity>::subdivide() {
    const auto x = m_rect.getX();
    const auto y = m_rect.getY();
    const auto w = m_rect.getWidth();
    const auto h = m_rect.getHeigth();

    const auto lt = Rect<float>(x , y, w / 2, h / 2);
    m_leftTop = std::make_unique<QuadTree<capacity>>(lt);
    const auto rt = Rect<float>(x + w / 2, y, w / 2, h / 2);
    m_rightTop = std::make_unique<QuadTree<capacity>>(rt);
    const auto lb = Rect<float>(x, y + h / 2, w / 2, h / 2);
    m_leftBottom = std::make_unique<QuadTree<capacity>>(lb);
    const auto rb = Rect<float>(x + w / 2, y + h / 2, w / 2, h / 2);
    m_rightBottom = std::make_unique<QuadTree<capacity>>(rb);

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
