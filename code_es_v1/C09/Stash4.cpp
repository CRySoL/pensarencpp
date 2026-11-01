//: C09:Stash4.cpp {O}
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
#include "Stash4.h"
#include <iostream>
#include <cassert>
using namespace std;
const int increment = 100;

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

void Stash::inflate(int increase) {
  assert(increase >= 0);
  if(increase == 0) return;
  int newQuantity = quantity + increase;
  int newBytes = newQuantity * size;
  int oldBytes = quantity * size;
  unsigned char* b = new unsigned char[newBytes];
  for(int i = 0; i < oldBytes; i++)
    b[i] = storage[i]; // Copiar lo antiguo en lo nuevo
  delete [](storage); // Liberar el almacenamiento antiguo
  storage = b; // Apuntar a la nueva memoria
  quantity = newQuantity; // Ajustar el tamaño
} ///:~
