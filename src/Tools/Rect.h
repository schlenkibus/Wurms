#pragma once

#include "Point.h"
template <typename T> class Rect {
public:
  Rect(T x, T y, T w, T h);
  const T &getX() const;
  const T &getY() const;
  const T &getWidth() const;
  const T &getHeigth() const;
  void setX(T x);
  void setY(T y);
  void setW(T w);
  void setH(T h);

  const Point<T> &getPosition() const;
  Point<T> &getPosition();
  bool contains(const Point<T>& p) const;

protected:
  Point<T> m_point;
  T m_w;
  T m_h;
};

template <typename T>
Rect<T>::Rect(T x, T y, T w, T h) : m_point(x, y), m_w{w}, m_h{h} {}
template <typename T> const T &Rect<T>::getX() const { return m_point.getX(); }
template <typename T> const T &Rect<T>::getY() const { return m_point.getY(); }
template <typename T> const T &Rect<T>::getWidth() const { return m_w; }
template <typename T> const T &Rect<T>::getHeigth() const { return m_h; }
template <typename T> const Point<T> &Rect<T>::getPosition() const {
  return m_point;
}
template <typename T> Point<T> &Rect<T>::getPosition() { return m_point; }
template <typename T> void Rect<T>::setX(T x) { m_point.setX(x); }
template <typename T> void Rect<T>::setY(T y) { m_point.setY(y); }
template <typename T> void Rect<T>::setW(T w) { m_w = w; }
template <typename T> void Rect<T>::setH(T h) { m_h = h; }
template <typename T> bool Rect<T>::contains(const Point<T> &p) const {
    return (p.getX() >= m_point.getX() &&
            p.getX() <=  m_point.getX() + m_w &&
            p.getY() >= m_point.getY() &&
            p.getY() <= m_point.getY() + m_h);
}
