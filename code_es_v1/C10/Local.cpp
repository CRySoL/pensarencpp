//: C10:Local.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Miembros estáticos y clases locales
#include <iostream>
using namespace std;

// Una clase anidada SÍ puede tener atributos estáticos:
class Outer {
  class Inner {
    static int i; // Correcto
  };
};

int Outer::Inner::i = 47;

// Una clase local no puede tener atributos estáticos:
void f() {
  class Local {
  public:
//! static int i;  // Error
    // (¿Cómo se definiría i?)
  } x;
} 

int main() { Outer x; f(); } ///:~
