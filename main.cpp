#include <iostream>

#include "./include/tree.h"
#include "./include/node.h"

int main() {
  std::string dna("AAGCTTTTTA");

  Splay::Tree<const char>* tree = new Splay::Tree<const char>(dna.data(), dna.length());


  auto [left, right] = tree->split(0);

  right->reverse();
  tree = Splay::Tree<const char>::join(left, right);

  for (size_t i=0; i<dna.length(); i++) {
    std::cout << tree->find(i)->value;
  }
  std::cout << std::endl;

  // std::cout << std::endl;
  // std::cout << tree->max_size() << std::endl;
  // for (size_t i=0; i<dna.length(); i++) {
  //   std::cout << tree->find(i)->value;
  // }

  // std::cout << std::endl;
  // // std::cout << tree->max_size() << std::endl;

  // auto [left, right] = tree->split(6); // AAGCTTT, TTA
 
  // right->reverse(); // AAGCTTT, ATT (not discharged)

  // tree = Splay::Tree<const char>::join(left, right); // AAGCTTTATT

  // std::cout << std::endl;
  // std::cout << tree->max_size() << std::endl;
  // for (size_t i=0; i<dna.length(); i++) {
  //   std::cout << tree->find(i)->value;
  // }
  // std::cout << std::endl;


  // Splay::Node<const char>* x = tree->find(3);

  // std::cout << x->value << std::endl;


  // Splay::Node<const char>* y = tree.find(2);

  // std::cout << y->value << std::endl;


  // Splay::Tree<const char> right = tree.split(3);
  // right.flip();
  // tree.join(right);
  // Splay::Node<const char>* x = tree.root->left->left;
  return 0;
}