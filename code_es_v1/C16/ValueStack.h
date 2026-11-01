//: C16:ValueStack.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Objetos guardados por valor en una Stack
#ifndef VALUESTACK_H
#define VALUESTACK_H
#include "../require.h"

template<class T, int ssize = 100>
class Stack {
  // El constructor por defecto inicializa
  // cada elemento del array:
  T stack[ssize];
  int top;
public:
  Stack() : top(0) {}
  // El constructor de copia lo copia en el array:
  void push(const T& x) {
    require(top < ssize, "Too many push()es");
    stack[top++] = x;
  }
  T peek() const { return stack[top]; }
  // El objeto sigue existiendo al sacarlo;
  // simplemente deja de estar disponible:
  T pop() {
    require(top > 0, "Too many pop()s");
    return stack[--top];
  }
};
#endif // VALUESTACK_H ///:~
