//: C07:Stash3.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Sobrecarga de funciones
#ifndef STASH3_H
#define STASH3_H

class Stash {
  int size;      // Tamaño de cada espacio
  int quantity;  // Número de espacios de almacenamiento
  int next;      // Siguiente espacio vacío
  // Array de bytes asignado dinámicamente:
  unsigned char* storage;
  void inflate(int increase);
public:
  Stash(int size); // Cantidad cero
  Stash(int size, int initQuantity);
  ~Stash();
  int add(void* element);
  void* fetch(int index);
  int count();
};
#endif // STASH3_H ///:~
