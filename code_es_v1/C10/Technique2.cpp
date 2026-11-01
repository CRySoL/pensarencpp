//: C10:Technique2.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
#include "Dependency2.h"
using namespace std;

// Devuelve un valor para poder llamarla como
// inicializador global:
int separator() {
  cout << "---------------------" << endl;
  return 1;
}

// Simula el problema de dependencias:
extern Dependency1 dep1;
Dependency2 dep2(dep1);
Dependency1 dep1;
int x1 = separator();

// Pero si ocurre en este orden, funciona bien:
Dependency1 dep1b;
Dependency2 dep2b(dep1b);
int x2 = separator();

// Envolver los objetos estáticos en funciones
// resuelve el problema
Dependency1& d1() {
  static Dependency1 dep1;
  return dep1;
}

Dependency2& d2() {
  static Dependency2 dep2(d1());
  return dep2;
}

int main() {
  Dependency2& dep2 = d2();
} ///:~
