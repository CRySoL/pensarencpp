//: C05:Stash.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Modificado para usar control de acceso
#ifndef STASH_H
#define STASH_H

class Stash {
  int size;      // Tamaño de cada espacio
  int quantity;  // Número de espacios de almacenamiento
  int next;      // Siguiente espacio vacío
  // Array de bytes asignado dinámicamente:
  unsigned char* storage;
  void inflate(int increase);
public:
  void initialize(int size);
  void cleanup();
  int add(void* element);
  void* fetch(int index);
  int count();
};
#endif // STASH_H ///:~
