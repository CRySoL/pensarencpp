//: C10:NamespaceOverriding1.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
#include "NamespaceMath.h"
int main() {
  using namespace Math;
  Integer a; // Oculta Math::a;
  a.setSign(negative);
  // Ahora hace falta la resolución de ámbito
  // para elegir Math::a :
  Math::a.setSign(positive);
} ///:~
