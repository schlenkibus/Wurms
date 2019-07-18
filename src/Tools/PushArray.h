#pragma once
#include <array>
#include <iterator>

template<typename T, size_t cap>
class PushArray {
public:
    PushArray();
    void push(T t);
    T& at(size_t index);
    const T& at(size_t index) const;
    const size_t size() const;
    constexpr size_t capacity() const;

protected:
    std::array<T, cap> m_array;
    size_t m_index;
};

template <typename T, size_t cap> PushArray<T, cap>::PushArray() : m_array{}, m_index{0} {
}

template <typename T, size_t cap>
void PushArray<T, cap>::push(T t) {
  if(m_index < cap) {
    m_array.at(m_index) = std::move(t);
  }
}

template <typename T, size_t cap>
T &PushArray<T, cap>::at(size_t index) {
  return m_array.at(index);
}

template <typename T, size_t cap>
const T &PushArray<T, cap>::at(size_t index) const {
    return m_array.at(index);
}
template <typename T, size_t cap>
const size_t PushArray<T, cap>::size() const {
  return m_array.size();
}
template <typename T, size_t cap>
constexpr size_t PushArray<T, cap>::capacity() const {
  return cap;
}
