//: C03:Assert.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Uso de la macro de depuración assert()
#include <cassert>  // Contiene la macro
using namespace std;

int main() {
  int i = 100;
  assert(i != 100); // Falla
} ///:~
