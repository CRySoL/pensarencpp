//: C14:Inheritance.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Herencia simple
#include "Useful.h"
#include <iostream>
using namespace std;

class Y : public X {
  int i; // Distinta de la i de X
public:
  Y() { i = 0; }
  int change() {
    i = permute(); // Llamada con otro nombre
    return i;
  }
  void set(int ii) {
    i = ii;
    X::set(ii); // Llamada con el mismo nombre
  }
};

int main() {
  cout << "sizeof(X) = " << sizeof(X) << endl;
  cout << "sizeof(Y) = "
       << sizeof(Y) << endl;
  Y D;
  D.change();
  // Se conserva la interfaz de funciones de X:
  D.read();
  D.permute();
  // Las funciones redefinidas ocultan las de la base:
  D.set(12);
} ///:~
