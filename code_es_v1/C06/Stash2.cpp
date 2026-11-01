//: C06:Stash2.cpp {O}
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Constructores y destructores
#include "Stash2.h"
#include "../require.h"
#include <iostream>
#include <cassert>
using namespace std;
const int increment = 100;

Stash::Stash(int sz) {
  size = sz;
  quantity = 0;
  storage = 0;
  next = 0;
}

int Stash::add(void* element) {
  if(next >= quantity) // ¿Queda espacio suficiente?
    inflate(increment);
  // Copiar el elemento en el almacenamiento,
  // a partir del siguiente espacio vacío:
  int startBytes = next * size;
  unsigned char* e = (unsigned char*)element;
  for(int i = 0; i < size; i++)
    storage[startBytes + i] = e[i];
  next++;
  return(next - 1); // Número de índice
}

void* Stash::fetch(int index) {
  require(0 <= index, "Stash::fetch (-)index");
  if(index >= next)
    return 0; // Para indicar el final
  // Devolver un puntero al elemento deseado:
  return &(storage[index * size]);
}

int Stash::count() {
  return next; // Número de elementos en CStash
}

void Stash::inflate(int increase) {
  require(increase > 0, 
    "Stash::inflate zero or negative increase");
  int newQuantity = quantity + increase;
  int newBytes = newQuantity * size;
  int oldBytes = quantity * size;
  unsigned char* b = new unsigned char[newBytes];
  for(int i = 0; i < oldBytes; i++)
    b[i] = storage[i]; // Copiar lo antiguo en lo nuevo
  delete [](storage); // Almacenamiento antiguo
  storage = b; // Apuntar a la nueva memoria
  quantity = newQuantity;
}

Stash::~Stash() {
  if(storage != 0) {
   cout << "freeing storage" << endl;
   delete []storage;
  }
} ///:~
