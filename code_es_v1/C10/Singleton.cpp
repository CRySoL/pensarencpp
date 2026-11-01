//: C10:Singleton.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Un miembro estático del mismo tipo garantiza
// que solo exista un objeto de ese tipo.
// También se conoce como patrón Único (Singleton).
#include <iostream>
using namespace std;

class Egg {
  static Egg e;
  int i;
  Egg(int ii) : i(ii) {}
  Egg(const Egg&); // Impide la construcción por copia
public:
  static Egg* instance() { return &e; }
  int val() const { return i; }
};

Egg Egg::e(47);

int main() {
//!  Egg x(1); // Error: no se puede crear un Egg
  // Se puede acceder a la única instancia:
  cout << Egg::instance()->val() << endl;
} ///:~
