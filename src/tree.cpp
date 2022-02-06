#include "../include/tree.h"

template <class T>
Splay::Tree<T>::Tree(T elements[], size_t length) {
  Splay::Node<T>* placeholder = new Node<T>(elements[0], 0, 0);

  Splay::Node<T>* current;
  Splay::Node<T>* child = placeholder;

  size_t i = 0;
  while (i < length) {
    current = new Node<T>(elements[i], 0, child->max+child->size);
    while (current->value == elements[i]) {
      current->size++;
      i++;
    }
    current->left = child;
    child->parent = current;

    child = current;
  }
  this->root = child;

  delete placeholder;
}

template <class T>
Splay::Tree<T>::~Tree() {
  delete this->root;
}

template <class T>
void Splay::Tree<T>::splay(Node<T>* x) {
  while (x->parent) {
    if (!x->parent->parent) {
      if (x->parent->left == x) {
        this->rotate_right(x);
      } else {
        this->rotate_left(x);
      }
    } else if (x->parent->parent->left == x->parent && x->parent->left == x) {
      this->rotate_right(x->parent);
      this->rotate_right(x);
    } else if (x->parent->parent->right == x->parent && x->parent->right == x) {
      this->rotate_left(x->parent);
      this->rotate_left(x);
    } else if (x->parent->parent->left == x->parent && x->parent->right == x) {
      this->rotate_left(x);
      this->rotate_right(x);
    } else {
      this->rotate_right(x);
      this->rotate_left(x);
    }
  }
}

template <class T>
void Splay::Tree<T>::rotate_right(Node<T>* x) {
  Node<T>* p = x->parent;
  Node<T>* g = p->parent;

  if (!g) {
    this->root = x;
    x->parent = nullptr;
  } else {
    if (g->left == p) {
      g->left = x;
    } else {
      g->right = x;
    }
    x->parent = g;
  }

  p->left = x->right;
  p->max = 0;
  if (p->left) {
    p->left->parent = p;
    p->max = p->left->max + p->left->size;
  }

  x->right = p;
  x->right->parent = x;
}

template <class T>
void Splay::Tree<T>::rotate_left(Node<T>* x) {
  Node<T>* p = x->parent;
  Node<T>* g = p->parent;

  if (!g) {
    this->root = x;
    x->parent = nullptr;
  } else {
    if (g->left == p) {
      g->left = x;
    } else {
      g->right = x;
    }
    x->parent = g;
  }

  p->right = x->left;
  if (p->right) {
    p->right->parent = p;
  }

  x->left = p;
  x->left->parent = x;
  x->max = p->max + p->size;
}

template <class T>
Splay::Node<T>* Splay::Tree<T>::find(size_t index) {
  Node<T>* x = this->root;
  size_t max = x->max;

  while (index < max || index >= max+x->size) {
    if (index < max) {
      max -= x->left->size;
      x = x->left;
    } else {
      max += x->right->size;
      x = x->right;
    }
  }

  this->splay(x);
  return x;
}

template class Splay::Tree<const char>;