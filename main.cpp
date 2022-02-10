#include <iostream>

#include "./include/tree.h"
#include "./include/node.h"

using namespace std;

int main() {

  int n, m;
  std::string ciag;

  ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> ciag;
    auto *tree = new Splay::Tree<const char>(ciag.data(), ciag.length());

    for (int i = 0; i < m; i++) {
        char polecenie;
        int j, k, l;
        cin >> polecenie >> j >> k;
        j--;
        k--;

        if (polecenie == 'O') {
            if (j == 0) {
                auto[p1, p2] = tree->split(k);
                p1->reverse();
                tree = Splay::Tree<const char>::join(p1, p2);
            } else {
                auto[p1, p2] = tree->split(j - 1);

                if (k == n - 1) {
                    p2->reverse();
                    tree = Splay::Tree<const char>::join(p1, p2);
                } else {
                    auto[p3, p4] = p2->split(k - j);
                    p3->reverse();
                    tree = Splay::Tree<const char>::join(Splay::Tree<const char>::join(p1, p3), p4);
                }
            }

        } else if (polecenie == 'P') {
            cin >> l;
            l--;

            if (j == 0) {
                if (l == 0) {

                } else {
                    auto[p1, p2] = tree->split(k);
                    auto[p3, p4] = p2->split(l - 1);
                    tree = Splay::Tree<const char>::join(Splay::Tree<const char>::join(p3, p1), p4);
                }
            } else {
                auto[p1, p2] = tree->split(j - 1);
                auto[p3, p4] = p2->split(k - j);

                if (l == 0) {
                    tree = Splay::Tree<const char>::join(Splay::Tree<const char>::join(p3, p1), p4);
                } else {
                    tree = Splay::Tree<const char>::join(p1, p4);
                    auto[p5, p6] = tree->split(l - 1);
                    tree = Splay::Tree<const char>::join(Splay::Tree<const char>::join(p5, p3), p6);
                }
            }

        } else if (polecenie == 'N') {
            if (j == 0) {
                if (k == n - 1) {
                    cout << tree->max_size() << '\n';
                } else {
                    auto[p1, p2] = tree->split(k);
                    cout << p1->max_size() << '\n';
                    tree = Splay::Tree<const char>::join(p1, p2);
                }
            } else {
                auto[p1, p2] = tree->split(j - 1);

                if (k == n - 1) {
                    cout << p1->max_size() << '\n';
                    tree = Splay::Tree<const char>::join(p1, p2);
                } else {
                    auto[p3, p4] = p2->split(k - j);
                    cout << p3->max_size() << '\n';
                    tree = Splay::Tree<const char>::join(Splay::Tree<const char>::join(p1, p3), p4);
                }
            }
        }
        for (size_t i=0; i<ciag.length(); i++) {
          std::cout << tree->find(i)->value;
        }
        std::cout << std::endl;
    }

  // std::string dna("AAGCTTTTTA");

  // Splay::Tree<const char>* tree = new Splay::Tree<const char>(dna.data(), dna.length());


  // auto [left, right] = tree->split(0);

  // right->reverse();
  // tree = Splay::Tree<const char>::join(left, right);

  // for (size_t i=0; i<dna.length(); i++) {
  //   std::cout << tree->find(i)->value;
  // }
  // std::cout << std::endl;

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