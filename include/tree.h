#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <utility>

#include "./node.h"

namespace Splay {
  template <class T>
  class Node;


  template <class T>
  class Tree {
  private:
    Node<T>* root;

    void splay(Node<T>* x);
    void rotate_right(Node<T>* x);
    void rotate_left(Node<T>* x);
    Node<T>* min();
    Node<T>* max();
    void discharge(Node<T>* x);
    Tree<T>(Node<T>* root): root{root} {};
  public:
    Tree<T>(T elements[], size_t length);
    ~Tree();

    Node<T>* find(size_t index);
    Tree<T> split(size_t index);
    void join(Tree<T> right);
    void flip();
  };
};

// #include "../src/tree.cpp"

#endif