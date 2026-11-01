//: C06:Stash2.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Con constructores y destructores
#ifndef STASH2_H
#define STASH2_H

class Stash {
  int size;      // Tamaño de cada espacio
  int quantity;  // Número de espacios de almacenamiento
  int next;      // Siguiente espacio vacío
  // Array de bytes asignado dinámicamente:
  unsigned char* storage;
  void inflate(int increase);
public:
  Stash(int size);
  ~Stash();
  int add(void* element);
  void* fetch(int index);
  int count();
};
#endif // STASH2_H ///:~
