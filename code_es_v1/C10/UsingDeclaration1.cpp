//: C10:UsingDeclaration1.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
#include "UsingDeclaration.h"
void h() {
  using namespace U; // Directiva using
  using V::f; // Declaración using
  f(); // Llama a V::f();
  U::f(); // Hay que calificarla por completo
}
int main() {} ///:~
