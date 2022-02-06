#include <iostream>

#include "./include/tree.h"

int main() {
  std::string dna("AGCTA");

  Splay::Tree<const char> tree(dna.data(), dna.length());
  return 0;
}