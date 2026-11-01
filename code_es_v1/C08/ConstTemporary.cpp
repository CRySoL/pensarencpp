//: C08:ConstTemporary.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Los objetos temporales son const

class X {};

X f() { return X(); } // Retorno por valor

void g1(X&) {} // Paso por referencia no const
void g2(const X&) {} // Paso por referencia const

int main() {
  // Error: f() crea un objeto temporal const:
//!  g1(f());
  // Correcto: g2 recibe una referencia const:
  g2(f());
} ///:~
