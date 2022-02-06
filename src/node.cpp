#include "../include/node.h"

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