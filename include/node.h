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

    size_t size;
    size_t max;
    bool flip;

    Node<T>(T value, size_t size, size_t max, bool flip = false): value{value}, size{size}, max{max}, flip{flip} {};
  public:
    ~Node<T>();
    
    T value;
  };
};


// #include "../src/node.cpp"
#endif