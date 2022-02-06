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
  public:
    Tree(T elements[], size_t length);
    ~Tree();

    Node<T>* find(size_t index);
    std::pair<Tree<T>, Tree<T>> split(size_t index);
    void join(Tree<T> left, Tree<T> right);
    void flip();
  };
};

// #include "../src/tree.cpp"

#endif