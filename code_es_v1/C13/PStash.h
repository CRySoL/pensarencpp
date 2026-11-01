//: C13:PStash.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Guarda punteros en lugar de objetos
#ifndef PSTASH_H
#define PSTASH_H

class PStash {
  int quantity; // Número de espacios
  int next; // Siguiente espacio vacío
   // Almacén de punteros:
  void** storage;
  void inflate(int increase);
public:
  PStash() : quantity(0), storage(0), next(0) {}
  ~PStash();
  int add(void* element);
  void* operator[](int index) const; // Obtener (fetch)
  // Quita la referencia de este PStash:
  void* remove(int index);
  // Número de elementos en el Stash:
  int count() const { return next; }
};
#endif // PSTASH_H ///:~
