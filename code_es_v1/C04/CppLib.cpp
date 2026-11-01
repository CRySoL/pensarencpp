//: C04:CppLib.cpp {O}
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Librería de C convertida a C++
// Declara la estructura y las funciones:
#include "CppLib.h"
#include <iostream>
#include <cassert>
using namespace std;
// Cantidad de elementos que se añaden
// al ampliar el almacenamiento:
const int increment = 100;

void Stash::initialize(int sz) {
  size = sz;
  quantity = 0;
  storage = 0;
  next = 0;
}

int Stash::add(const void* element) {
  if(next >= quantity) // ¿Queda espacio suficiente?
    inflate(increment);
  // Copia el elemento en el almacenamiento,
  // a partir del siguiente espacio libre:
  int startBytes = next * size;
  unsigned char* e = (unsigned char*)element;
  for(int i = 0; i < size; i++)
    storage[startBytes + i] = e[i];
  next++;
  return(next - 1); // Número de índice
}

void* Stash::fetch(int index) {
  // Comprueba los límites del índice:
  assert(0 <= index);
  if(index >= next)
    return 0; // Para indicar el final
  // Devuelve un puntero al elemento pedido:
  return &(storage[index * size]);
}

int Stash::count() {
  return next; // Número de elementos de CStash
}

void Stash::inflate(int increase) {
  assert(increase > 0);
  int newQuantity = quantity + increase;
  int newBytes = newQuantity * size;
  int oldBytes = quantity * size;
  unsigned char* b = new unsigned char[newBytes];
  for(int i = 0; i < oldBytes; i++)
    b[i] = storage[i]; // Copia lo viejo en lo nuevo
  delete []storage; // Almacenamiento antiguo
  storage = b; // Apunta a la memoria nueva
  quantity = newQuantity;
}

void Stash::cleanup() {
  if(storage != 0) {
    cout << "freeing storage" << endl;
    delete []storage;
  }
} ///:~
