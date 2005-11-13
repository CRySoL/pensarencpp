//: C06:Constructor1.cpp
// Constructors & destructors
#include <iostream>
using namespace std;

class Tree {
  int height;
public:
  Tree(int initialHeight);  // Constructor
  ~Tree();  // Destructor
  void grow(int years);
  void printsize();
};

Tree::Tree(int initialHeight) {
  height = initialHeight;
}

Tree::~Tree() {
  cout << "dentro del destructor de Tree" << endl;
  printsize();
}

void Tree::grow(int years) {
  height += years;
}

void Tree::printsize() {
  cout << "la altura del árbol es " << height << endl;
}

int main() {
  cout << "antes de la llave de apertura" << endl;
  {
    Tree t(12);
    cout << "después de la creación de Tree" << endl;
    t.printsize();
    t.grow(4);
    cout << "antes de la llave de cierre" << endl;
  }
  cout << "después de la llave de cierre" << endl;
} ///:~
