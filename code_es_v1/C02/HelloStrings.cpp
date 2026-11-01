//: C02:HelloStrings.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Lo básico de la clase string de C++ estándar
#include <string>
#include <iostream>
using namespace std;

int main() {
  string s1, s2; // Cadenas vacías
  string s3 = "Hello, World."; // Inicializada
  string s4("I am"); // También inicializada
  s2 = "Today"; // Asignar a una cadena
  s1 = s3 + " " + s4; // Combinar cadenas
  s1 += " 8 "; // Añadir al final de una cadena
  cout << s1 + s2 + "!" << endl;
} ///:~
