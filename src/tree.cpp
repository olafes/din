#include "../include/tree.h"

// template <class T>
// Splay::Tree<T>::Tree(Node<T>* root)

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
  // delete this->root;
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
Splay::Node<T>* Splay::Tree<T>::min() {
  if (!this->root) {
    return nullptr;
  }
  Node<T>* min = this->root;
  while (min->left) {
    min = min->left;
  }
  return min;
}

template <class T>
Splay::Node<T>* Splay::Tree<T>::max() {
  if (!this->root) {
    return nullptr;
  }
  Node<T>* max = this->root;
  while (max->right) {
    max = max->right;
  }
  return max;
}


template <class T>
void Splay::Tree<T>::discharge(Node<T>* x) {
  if (x) {
    if (x->flip) {
      Node<T>* tmp = x->left;
      x->left = x->right;
      x->right = tmp;
      x->flip = false;
    }

    this->discharge(x->left);
    this->discharge(x->right);

    if (x->left) {
      x->max = x->left->max + x->left->size;
    } else {
      x->max = 0;
    }
  }

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

template <class T>
Splay::Tree<T> Splay::Tree<T>::split(size_t index) {
  Splay::Node<T>* x = this->find(index);
  Splay::Node<T>* y;

  size_t delta = x->max - index + 1;
  if (delta == x->size) {
    y = x->right;
    if (y) {
      y->parent = nullptr;
    }
    x->right = nullptr;
  } else {
    y = new Node<T>(x->value, x->size-delta, 0);
    x->size = delta;
    y->right = x->right;
    if (y->right) {
      y->right->parent = y;
    }
    x->right = nullptr;
  }

  return Splay::Tree<T>(y);
}

template <class T>
void Splay::Tree<T>::join(Tree<T> right) {
  Node<T>* x_1 = this->max();
  Node<T>* x_2 = right.min();

  if (!x_1) {
    this->root = x_2;
    return;
  }
  if (!x_2) {
    return;
  }
  this->splay(x_1);
  right.splay(x_2);
  if (x_1->value == x_2->value) {
    x_1->size += x_2->size;
    x_1->right = x_2->right;
    if (x_1->right) {
      x_1->right->parent = x_1;
    }
  } else {
    x_1->right = x_2;
    x_1->right->parent = x_1;
  }
}

template <class T>
void Splay::Tree<T>::flip() {
  if (this->root) {
    this->root->flip = !this->root->flip;
  }
}

template class Splay::Tree<const char>;