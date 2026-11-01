//: C14:Composition.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Reutilización de código mediante composición
#include "Useful.h"

class Y {
  int i;
public:
  X x; // Objeto incrustado
  Y() { i = 0; }
  void f(int ii) { i = ii; }
  int g() const { return i; }
};

int main() {
  Y y;
  y.f(47);
  y.x.set(37); // Acceso al objeto incrustado
} ///:~
