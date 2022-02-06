#ifndef NODE_H
#define NODE_H

#include <cstddef>

#include "./tree.h"

namespace Splay {
  template <class T>
  class Tree;

  template <class T>
  class Node {
  private:
    friend class Tree<T>;  

    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;

    size_t subtree_sizes_sum;
    bool flip;

    size_t subtree_sizes_max;

    Node<T>(T value, size_t size, size_t subtree_sizes_sum, bool flip = false);
    ~Node<T>();
  public:
    const T value;
    const size_t size;
  };
};

#endif