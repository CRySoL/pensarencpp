//: C09:Stash4.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Funciones inline
#ifndef STASH4_H
#define STASH4_H
#include "../require.h"

class Stash {
  int size;      // Tamaño de cada espacio
  int quantity;  // Número de espacios de almacenamiento
  int next;      // Siguiente espacio vacío
  // Array de bytes asignado dinámicamente:
  unsigned char* storage;
  void inflate(int increase);
public:
  Stash(int sz) : size(sz), quantity(0),
    next(0), storage(0) {}
  Stash(int sz, int initQuantity) : size(sz), 
    quantity(0), next(0), storage(0) { 
    inflate(initQuantity); 
  }
  Stash::~Stash() {
    if(storage != 0) 
      delete []storage;
  }
  int add(void* element);
  void* fetch(int index) const {
    require(0 <= index, "Stash::fetch (-)index");
    if(index >= next)
      return 0; // Para indicar el final
    // Devolver un puntero al elemento deseado:
    return &(storage[index * size]);
  }
  int count() const { return next; }
};
#endif // STASH4_H ///:~
