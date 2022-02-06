#ifndef NODE_H
#define NODE_H

#include "./tree.h";

namespace Splay {
  template <class T>
  class Node {
  private:
    friend class Splay::Tree<T>;  

    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;

    T value;
    size_t size;
    size_t max;
    bool flip;
  public:
    Node<T>(T value, size_t size) {value, size, size, false};
    T value();
  };
};

#endif