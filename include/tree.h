#ifndef TREE_H
#define TREE_H

#include <cstddef>
#include <utility>
#include <tuple>
#include <algorithm>

#include "./node.h"

namespace Splay {
  template <class T>
  class Node;

  template <class T>
  class Tree {
  private:
    mutable Node<T>* root;

    void splay(Node<T>* x) const;
    void rotate_right(Node<T>* x) const;
    void rotate_left(Node<T>* x) const;
    void discharge(Node<T>* x) const;
    void update(Node<T>* x) const;

    Tree<T>(Node<T>* root);
    ~Tree();
  public:
    Tree<T>(T elements[], size_t length);

    Node<T>* min() const;
    Node<T>* max() const;
    Node<T>* find(size_t index) const;

    void reverse();
    std::tuple<Tree<T>*, Tree<T>*> split(size_t index);
    static Tree<T>* join(Tree<T>* left, Tree<T>* right);
    
    size_t max_size() const;
  };
};

#endif