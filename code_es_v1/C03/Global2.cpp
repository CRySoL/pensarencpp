//: C03:Global2.cpp {O}
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Acceso a variables globales externas
extern int globe;  
// (El enlazador resuelve la referencia)
void func() {
  globe = 47;
} ///:~
