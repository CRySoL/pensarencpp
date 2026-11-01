//: C03:Forward.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Declaraciones adelantadas de funciones y datos
#include <iostream>
using namespace std;

// En realidad esto no es externo, pero hay que decirle
// al compilador que existe en algún sitio:
extern int i; 
extern void func();
int main() {
  i = 0;
  func();
}
int i; // La definición del dato
void func() {
  i++;
  cout << i;
} ///:~
