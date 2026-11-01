//: C03:AutoIncrement.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Muestra el uso de los operadores de
// autoincremento y autodecremento.
#include <iostream>
using namespace std;

int main() {
  int i = 0;
  int j = 0;
  cout << ++i << endl; // Preincremento
  cout << j++ << endl; // Postincremento
  cout << --i << endl; // Predecremento
  cout << j-- << endl; // Postdecremento
} ///:~
