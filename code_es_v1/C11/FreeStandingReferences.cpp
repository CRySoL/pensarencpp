//: C11:FreeStandingReferences.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
#include <iostream>
using namespace std;

// Referencia independiente normal:
int y;
int& r = y;
// Al crear una referencia, hay que
// inicializarla con un objeto vivo.
// Sin embargo, también se puede escribir:
const int& q = 12;  // (1)
// Las referencias se ligan a la memoria de otro:
int x = 0;          // (2)
int& a = x;         // (3)
int main() {
  cout << "x = " << x << ", a = " << a << endl;
  a++;
  cout << "x = " << x << ", a = " << a << endl;
} ///:~
