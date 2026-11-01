//: C16:IterStackTemplate.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Plantilla de pila sencilla con iterador anidado
#ifndef ITERSTACKTEMPLATE_H
#define ITERSTACKTEMPLATE_H
#include "../require.h"
#include <iostream>

template<class T, int ssize = 100>
class StackTemplate {
  T stack[ssize];
  int top;
public:
  StackTemplate() : top(0) {}
  void push(const T& i) {
    require(top < ssize, "Too many push()es");
    stack[top++] = i;
  }
  T pop() {
    require(top > 0, "Too many pop()s");
    return stack[--top];
  }
  class iterator; // Declaración necesaria
  friend class iterator; // Hacerlo amigo
  class iterator { // Ahora se define
    StackTemplate& s;
    int index;
  public:
    iterator(StackTemplate& st): s(st),index(0){}
    // Para crear el iterador "centinela final":
    iterator(StackTemplate& st, bool) 
      : s(st), index(s.top) {}
    T operator*() const { return s.stack[index];}
    T operator++() { // Forma prefija
      require(index < s.top, 
        "iterator moved out of range");
      return s.stack[++index];
    }
    T operator++(int) { // Forma postfija
      require(index < s.top, 
        "iterator moved out of range");
      return s.stack[index++];
    }
    // Salto del iterador hacia delante
    iterator& operator+=(int amount) {
      require(index + amount < s.top,
        " StackTemplate::iterator::operator+=() "
        "tried to move out of bounds");
      index += amount;
      return *this;
    }
    // Para saber si se ha llegado al final:
    bool operator==(const iterator& rv) const {
      return index == rv.index;
    }
    bool operator!=(const iterator& rv) const {
      return index != rv.index;
    }
    friend std::ostream& operator<<(
      std::ostream& os, const iterator& it) {
      return os << *it;
    }
  };
  iterator begin() { return iterator(*this); }
  // Crea el "centinela final":
  iterator end() { return iterator(*this, true);}
};
#endif // ITERSTACKTEMPLATE_H ///:~
