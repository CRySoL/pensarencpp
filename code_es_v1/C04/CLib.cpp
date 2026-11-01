//: C04:CLib.cpp {O}
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Implementación de la librería de ejemplo al estilo C
// Declara la estructura y las funciones:
#include "CLib.h"
#include <iostream>
#include <cassert> 
using namespace std;
// Cantidad de elementos que se añaden
// al ampliar el almacenamiento:
const int increment = 100;

void initialize(CStash* s, int sz) {
  s->size = sz;
  s->quantity = 0;
  s->storage = 0;
  s->next = 0;
}

int add(CStash* s, const void* element) {
  if(s->next >= s->quantity) //¿Queda espacio suficiente?
    inflate(s, increment);
  // Copia el elemento en el almacenamiento,
  // a partir del siguiente espacio libre:
  int startBytes = s->next * s->size;
  unsigned char* e = (unsigned char*)element;
  for(int i = 0; i < s->size; i++)
    s->storage[startBytes + i] = e[i];
  s->next++;
  return(s->next - 1); // Número de índice
}

void* fetch(CStash* s, int index) {
  // Comprueba los límites del índice:
  assert(0 <= index);
  if(index >= s->next)
    return 0; // Para indicar el final
  // Devuelve un puntero al elemento pedido:
  return &(s->storage[index * s->size]);
}

int count(CStash* s) {
  return s->next;  // Elementos de CStash
}

void inflate(CStash* s, int increase) {
  assert(increase > 0);
  int newQuantity = s->quantity + increase;
  int newBytes = newQuantity * s->size;
  int oldBytes = s->quantity * s->size;
  unsigned char* b = new unsigned char[newBytes];
  for(int i = 0; i < oldBytes; i++)
    b[i] = s->storage[i]; // Copia lo viejo en lo nuevo
  delete [](s->storage); // Almacenamiento antiguo
  s->storage = b; // Apunta a la memoria nueva
  s->quantity = newQuantity;
}

void cleanup(CStash* s) {
  if(s->storage != 0) {
   cout << "freeing storage" << endl;
   delete []s->storage;
  }
} ///:~
