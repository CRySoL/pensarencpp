//: C04:Scoperes.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Resolución de ámbito global
int a;
void f() {}

struct S {
  int a;
  void f();
};

void S::f() {
  ::f();  // ¡Si no, sería recursiva!
  ::a++;  // Selecciona la a global
  a--;    // La a del ámbito de la struct
}
int main() { S s; f(); } ///:~
