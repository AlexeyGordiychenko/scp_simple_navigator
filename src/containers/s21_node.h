#ifndef S21_A2_CONTAINERS_NODE_H_
#define S21_A2_CONTAINERS_NODE_H_

#include <cstdlib>

namespace s21 {

template <class T>
class s21_node {
 private:
 public:
  T *data_;
  s21_node *prev_;
  s21_node *next_;
  int id = rand();

  s21_node();
  s21_node(T *data);
  ~s21_node();

  void set_next(s21_node<T> *n);
};

template <class T>
inline void s21_node<T>::set_next(s21_node<T> *n) {
  next_->prev_ = n;
  n->next_ = next_;
  n->prev_ = this;
  next_ = n;
}

template <class T>
inline s21_node<T>::s21_node()
    : data_(nullptr), prev_(nullptr), next_(nullptr) {}

template <class T>
inline s21_node<T>::~s21_node() {
  if (data_) delete data_;
}
}  // namespace s21

#endif  // S21_A2_CONTAINERS_NODE_H_
