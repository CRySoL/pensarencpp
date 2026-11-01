//: C04:CppLib.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Librería al estilo C convertida a C++

struct Stash {
  int size;      // Tamaño de cada espacio
  int quantity;  // Número de espacios de almacenamiento
  int next;      // Siguiente espacio libre
   // Array de bytes reservado dinámicamente:
  unsigned char* storage;
  // ¡Funciones!
  void initialize(int size);
  void cleanup();
  int add(const void* element);
  void* fetch(int index);
  int count();
  void inflate(int increase);
}; ///:~
