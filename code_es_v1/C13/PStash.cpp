//: C13:PStash.cpp {O}
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Definiciones del Stash de punteros
#include "PStash.h"
#include "../require.h"
#include <iostream>
#include <cstring> // Funciones 'mem'
using namespace std;

int PStash::add(void* element) {
  const int inflateSize = 10;
  if(next >= quantity)
    inflate(inflateSize);
  storage[next++] = element;
  return(next - 1); // Número de índice
}

// No es propietario de los objetos:
PStash::~PStash() {
  for(int i = 0; i < next; i++)
    require(storage[i] == 0, 
      "PStash not cleaned up");
  delete []storage; 
}

// Sobrecarga de operadores en lugar de fetch
void* PStash::operator[](int index) const {
  require(index >= 0,
    "PStash::operator[] index negative");
  if(index >= next)
    return 0; // Para indicar el final
  // Produce el puntero al elemento deseado:
  return storage[index];
}

void* PStash::remove(int index) {
  void* v = operator[](index);
  // "Quita" el puntero:
  if(v != 0) storage[index] = 0;
  return v;
}

void PStash::inflate(int increase) {
  const int psz = sizeof(void*);
  void** st = new void*[quantity + increase];
  memset(st, 0, (quantity + increase) * psz);
  memcpy(st, storage, quantity * psz);
  quantity += increase;
  delete []storage; // Espacio antiguo
  storage = st; // Apunta a la memoria nueva
} ///:~
