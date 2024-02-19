#ifndef S21_A2_CONTAINERS_STACK_H_
#define S21_A2_CONTAINERS_STACK_H_

#include <cstddef>
#include <initializer_list>
#include <utility>

#include "s21_list.h"
#include "s21_node.h"

namespace s21 {
template <class T, class C = list<T>>
class stack {
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef size_t size_type;

 private:
  C list_;

 public:
  stack() noexcept;
  stack(std::initializer_list<value_type> const &items) noexcept;
  stack(const stack &q) noexcept;
  stack(stack &&q) noexcept;
  ~stack();
  stack<T, C> &operator=(stack &&q) noexcept;
  stack<T, C> &operator=(const stack &q) noexcept;

  const_reference top() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  void push(const_reference value) noexcept;
  void pop() noexcept;
  void swap(stack &other) noexcept;

  template <class... Args>
  void insert_many_front(Args &&...args) noexcept {
    list_.insert_many_back(args...);
  }
};

template <class T, class C>
inline stack<T, C>::stack() noexcept {}

template <class T, class C>
inline stack<T, C>::stack(
    std::initializer_list<value_type> const &items) noexcept {
  list_ = list(items);
}

template <class T, class C>
inline stack<T, C>::stack(const stack &q) noexcept {
  list_ = list(q.list_);
}

template <class T, class C>
inline stack<T, C>::stack(stack &&q) noexcept {
  list_ = std::move(q.list_);
}

template <class T, class C>
inline stack<T, C>::~stack() {}

template <class T, class C>
inline stack<T, C> &stack<T, C>::operator=(stack &&q) noexcept {
  list_ = std::move(q.list_);
  return *this;
}

template <class T, class C>
inline stack<T, C> &stack<T, C>::operator=(const stack &q) noexcept {
  list_ = q.list_;
  return *this;
}

template <class T, class C>
inline typename stack<T, C>::const_reference stack<T, C>::top() const noexcept {
  return list_.back();
}

template <class T, class C>
inline bool stack<T, C>::empty() const noexcept {
  return list_.empty();
}

template <class T, class C>
inline typename stack<T, C>::size_type stack<T, C>::size() const noexcept {
  return list_.size();
}

template <class T, class C>
inline void stack<T, C>::push(const_reference value) noexcept {
  list_.push_back(value);
}

template <class T, class C>
inline void stack<T, C>::pop() noexcept {
  list_.pop_back();
}

template <class T, class C>
inline void stack<T, C>::swap(stack &other) noexcept {
  list_.swap(other.list_);
}

}  // namespace s21

#endif  // S21_A2_CONTAINERS_STACK_H_
