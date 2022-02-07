#ifndef DIN_H
#define DIN_H

#include <cstddef>
#include <string>

#include "./tree.h"

class Din {
private:
  Splay::Tree<const char>* dna;
public:
  Din(std::string* string);
  ~Din();

  void o(size_t j, size_t k);
  void p(size_t j, size_t k, size_t l);
  size_t n(size_t j, size_t k);
};

#endif