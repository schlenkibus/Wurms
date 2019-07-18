#pragma once

template <typename T> class Point {
public:
  Point();
  Point(T x, T y);
  const T &getX() const;
  const T &getY() const;

  void setX(T x);
  void setY(T y);

protected:
  T m_x;
  T m_y;
};
template <typename T> Point<T>::Point() {
    m_x = 0;
    m_y = 0;
}
template <typename T> Point<T>::Point(T x, T y) : m_x{x}, m_y{y} {
}
template <typename T> const T &Point<T>::getX() const {
  return m_x;
}
template <typename T> const T &Point<T>::getY() const {
  return m_y;
}
template <typename T> void Point<T>::setX(T x) {
    m_x = x;
}
template <typename T> void Point<T>::setY(T y) {
    m_y = y;
}
