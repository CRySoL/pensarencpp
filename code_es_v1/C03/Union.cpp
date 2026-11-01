//: C03:Union.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Tamaño y uso sencillo de una union
#include <iostream>
using namespace std;

union Packed { // Declaración similar a una clase
  char i;
  short j;
  int k;
  long l;
  float f;
  double d;  
  // La union tendrá el tamaño de un double,
  // ya que es el elemento más grande
};  // Una union termina en punto y coma, como una struct

int main() {
  cout << "sizeof(Packed) = " 
       << sizeof(Packed) << endl;
  Packed x;
  x.i = 'c';
  cout << x.i << endl;
  x.d = 3.14159;
  cout << x.d << endl;
} ///:~
