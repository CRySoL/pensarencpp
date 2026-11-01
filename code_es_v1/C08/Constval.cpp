//: C08:Constval.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Devolver constantes por valor
// no tiene sentido con los tipos predefinidos

int f3() { return 1; }
const int f4() { return 1; }

int main() {
  const int j = f3(); // Funciona bien
  int k = f4(); // ¡Pero esto también funciona!
} ///:~
