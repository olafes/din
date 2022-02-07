#include "../include/din.h"

Din::Din(std::string* string) {
  this->dna = new Splay::Tree<const char>(string->data(), string->length());
}

Din::~Din() {
  delete this->dna;
}

void Din::o(size_t j, size_t k) {
  // auto [tmp, right] = this->dna->split(k-1);
  // if (j == 1) {
  //   tmp->reverse();
  //   this->dna = Splay::Tree<const char>::join(tmp, right);
  // } else {
  //   auto [left, mid] = tmp->split(j-1);
  //   mid->reverse();
  //   this->dna = Splay::Tree<const char>::join(left, Splay::Tree<const char>::join(mid, right));
  // }
}

void Din::p(size_t j, size_t k, size_t l) {
  
}

size_t Din::n(size_t j, size_t k) {
  
}