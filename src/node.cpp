#include "../include/node.h"

template <class T>
Splay::Node<T>::Node(T value, size_t size, size_t subtree_sizes_sum, size_t subtree_sizes_max, bool flip): value{value}, size{size}, subtree_sizes_sum{subtree_sizes_sum}, size_t subtree_sizes_max{size_t subtree_sizes_max}, flip{flip} {};

template<class T>
Splay::Node<T>::~Node() {
  delete this->left;
  delete this->right;

  if (this->parent) {
    if (this->parent->left == this) {
      this->parent->left = nullptr;
    } else {
      this->parent->right = nullptr;
    }
  }
}

template class Splay::Node<const char>;