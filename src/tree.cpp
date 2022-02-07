#include "../include/tree.h"

template <class T>
Splay::Tree<T>::Tree(Node<T>* root): root{root} {};

template <class T>
Splay::Tree<T>::Tree(T elements[], size_t length) {
  Splay::Node<T>* placeholder = new Node<T>(elements[0], 0, 0);

  Splay::Node<T>* current = nullptr;
  Splay::Node<T>* child = placeholder;

  struct {
    T* value;
    size_t size;
    size_t substree_sizes_sum;
    size_t substree_sizes_max;
  } data;

  size_t i = 0;
  while (i < length) {
    data = {&elements[i], 0, child->subtree_sizes_sum + child->size, std::max(child->size, child->subtree_sizes_max)};
    while (*(data.value) == elements[i]) {
      data.size++;
      i++;
    }
    current = new Node<T>(*(data.value), data.size, data.substree_sizes_sum, data.substree_sizes_max);
    current->left = child;
    child->parent = current;

    child = current;
  }
  this->root = current;

  delete placeholder;
}

template<class T>
Splay::Tree<T>::~Tree() {
  delete this->root;
}

// x must not be a nullptr
template <class T>
void Splay::Tree<T>::splay(Node<T>* x) const {
  while (x->parent) {
    if (!x->parent->parent) {
      this->discharge(x->parent);
      this->discharge(x);

      if (x->parent->left == x) {
        this->rotate_right(x);
      } else {
        this->rotate_left(x);
      }
    } else {
      this->discharge(x->parent->parent);
      this->discharge(x->parent);
      this->discharge(x);

      if (x->parent->parent->left == x->parent && x->parent->left == x) {
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

  this->discharge(x);
}

// x must not be a nullptr
// x->parent must not be a nullptr
template <class T>
void Splay::Tree<T>::rotate_right(Node<T>* x) const {
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
  if (p->left) {
    p->left->parent = p;
  }

  x->right = p;
  x->right->parent = x;

  this->update(p);
  this->update(x);
}

// x must not be a nullptr
// x->parent must not be a nullptr
template <class T>
void Splay::Tree<T>::rotate_left(Node<T>* x) const {
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

  this->update(p);
  this->update(x);
}

// x must not be a nullptr
template <class T>
void Splay::Tree<T>::discharge(Node<T>* x) const {
  if (x->flip) {
    x->flip = false;
    if (x->left) {
      x->left->flip ^= 1;
    }
    if (x->right) {
      x->right->flip ^= 1;
    }
    std::swap(x->left, x->right);
  }
}

// x must not be a nullptr
template <class T>
void Splay::Tree<T>::update(Node<T>* x) const {
  size_t subtree_sizes_sum = 0;
  size_t subtree_sizes_max = 0;
  if (x->left) {
    subtree_sizes_sum += x->left->subtree_sizes_sum + x->left->size;
    subtree_sizes_max = std::max({subtree_sizes_max, x->left->subtree_sizes_max, x->left->size});
  }
  if (x->right) {
    subtree_sizes_sum += x->right->subtree_sizes_sum + x->right->size;
    subtree_sizes_max = std::max({subtree_sizes_max, x->right->subtree_sizes_max, x->right->size});
  }

  x->subtree_sizes_sum = subtree_sizes_sum;
  x->subtree_sizes_max = subtree_sizes_max;
}


template <class T>
Splay::Node<T>* Splay::Tree<T>::min() const {
  Node<T>* m = this->root;
  if (!m) {
    return nullptr;
  }
  this->discharge(m);
  while (m->left) {
    m = m->left;
    this->discharge(m);
  }
  return m;
}

template <class T>
Splay::Node<T>* Splay::Tree<T>::max() const {
  Node<T>* m = this->root;
  if (!m) {
    return nullptr;
  }
  this->discharge(m);
  while (m->right) {
    m = m->right;
    this->discharge(m);
  }
  return m;
}

template <class T>
Splay::Node<T>* Splay::Tree<T>::find(size_t index) const {
  Node<T>* x = this->root;
  if (x) {
    size_t left_subtree_size_sum;
    do {
      this->discharge(x);
      left_subtree_size_sum = (x->left) ? x->left->subtree_sizes_sum+x->left->size : 0;

      if (index < left_subtree_size_sum) {
        x = x->left;
      } else if (index >= left_subtree_size_sum+x->size) {
        x = x->right;
      } else {
        break;
      }
    } while (true);

    this->splay(x);
  }
  return x;
}

// can be called on an empty tree
template <class T>
void Splay::Tree<T>::reverse() {
  if (this->root) {
    this->root->flip ^= 1;
  }
}

// can be called on an empty tree
// index must be valid on non-empty tree

// calling this function consumes tree object
template <class T>
std::tuple<Splay::Tree<T>*, Splay::Tree<T>*> Splay::Tree<T>::split(size_t index) {
  if (!this->root) {
    return std::make_tuple(new Tree<T>(nullptr), new Tree<T>(nullptr));
  }
  Node<T>* x = this->find(index);
  Node<T>* y;

  size_t x_0 = (x->left) ? x->left->subtree_sizes_sum + x->left->size : 0;
  size_t delta = index - x_0 + 1;
  if (delta == x->size) {
    y = x->right;
    if (y) {
      y->parent = nullptr;
    }
    x->right = nullptr;
  } else {
    y = new Node<T>(x->value, x->size-delta, 0);
    y->right = x->right;
    if (y->right) {
      y->right->parent = y;
    }
    x->right = nullptr;

    T value = x->value;
    Node<T>* left = x->left;

    x->left->parent = nullptr;
    x->left = nullptr;
    delete x;

    x = new Node<T>(value, delta, 0);
    x->left = left;
    if (x->left) {
      x->left->parent = x;
    }

    this->update(y);
  }
  this->update(x);

  this->root = nullptr;
  delete this;

  return std::make_tuple(new Tree<T>(x), new Tree<T>(y));
}

// can be called with empty trees
// calling this function consumes left and right
template <class T>
Splay::Tree<T>* Splay::Tree<T>::join(Tree<T>* left, Tree<T>* right) {
  Tree<T>* merged;
  if (left->root && right->root) {
    Node<T>* x = left->max();
    left->splay(x);
    Node<T>* y = right->min();
    right->splay(y);

    if (x->value != y->value) {
      x->right = y;
      x->right->parent = x;
      merged = new Tree<T>(x);
    } else {
      size_t size = x->size + y->size;
      Node<T>* z = new Node<T>(x->value, size, 0);

      z->left = x->left;
      if (z->left) {
        z->left->parent = z;
      }
      x->left = nullptr;
      delete x;

      z->right = y->right;
      if (z->right) {
        z->right->parent = z;
      }
      y->right = nullptr;
      delete y;

      merged = new Tree<T>(z);
    }
  } else if (!left->root) {
    merged = new Tree<T>(right->root);
  } else if (!right->root) {
    merged = new Tree<T>(left->root);
  } else {
    merged = new Tree<T>(nullptr);
  }

  if (merged->root) {
    merged->update(merged->root);
  }

  left->root = nullptr;
  delete left;
  right->root = nullptr;
  delete right;

  return merged;
}

template class Splay::Tree<const char>;