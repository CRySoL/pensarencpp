//: C08:Safecons.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Uso de const por seguridad
#include <iostream>
using namespace std;

const int i = 100;  // Constante típica
const int j = i + 10; // Valor de una expresión const
long address = (long)&j; // Obliga a reservar espacio
char buf[j + 10]; // Sigue siendo una expresión const

int main() {
  cout << "type a character & CR:";
  const char c = cin.get(); // No se puede cambiar
  const char c2 = c + 'a';
  cout << c2;
  // ...
} ///:~
