//: C03:PointerToFunction.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Definición y uso de un puntero a función
#include <iostream>
using namespace std;

void func() {
  cout << "func() called..." << endl;
}

int main() {
  void (*fp)();  // Define un puntero a función
  fp = func;  // Lo inicializa
  (*fp)();    // Al dereferenciarlo se llama a la función
  void (*fp2)() = func;  // Define e inicializa
  (*fp2)();
} ///:~
