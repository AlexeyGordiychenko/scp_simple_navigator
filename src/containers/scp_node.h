#ifndef SCP_A2_CONTAINERS_NODE_H_
#define SCP_A2_CONTAINERS_NODE_H_

#include <cstdlib>

namespace scp {

template <class T>
class scp_node {
 private:
 public:
  T *data_;
  scp_node *prev_;
  scp_node *next_;
  int id = rand();

  scp_node();
  scp_node(T *data);
  ~scp_node();

  void set_next(scp_node<T> *n);
};

template <class T>
inline void scp_node<T>::set_next(scp_node<T> *n) {
  next_->prev_ = n;
  n->next_ = next_;
  n->prev_ = this;
  next_ = n;
}

template <class T>
inline scp_node<T>::scp_node()
    : data_(nullptr), prev_(nullptr), next_(nullptr) {}

template <class T>
inline scp_node<T>::~scp_node() {
  if (data_) delete data_;
}
}  // namespace scp

#endif  // SCP_A2_CONTAINERS_NODE_H_
