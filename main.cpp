#include <iostream>

#include "./include/tree.h"
#include "./include/node.h"

int main() {
  std::string dna("AAGCTTTTTA");

  Splay::Tree<const char> tree(dna.data(), dna.length());
  Splay::Node<const char>* x = tree.find(4);
  Splay::Node<const char>* y = tree.find(2);

  std::cout << x->value << std::endl;
  std::cout << y->value << std::endl;

  // Splay::Node<const char>* x = tree.root->left->left;
  return 0;
}