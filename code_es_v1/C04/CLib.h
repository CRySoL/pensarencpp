//: C04:CLib.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Fichero de cabecera de una librería al estilo C
// Una especie de array creado en tiempo de ejecución

typedef struct CStashTag {
  int size;      // Tamaño de cada espacio
  int quantity;  // Número de espacios de almacenamiento
  int next;      // Siguiente espacio libre
  // Array de bytes reservado dinámicamente:
  unsigned char* storage;
} CStash;

void initialize(CStash* s, int size);
void cleanup(CStash* s);
int add(CStash* s, const void* element);
void* fetch(CStash* s, int index);
int count(CStash* s);
void inflate(CStash* s, int increase);
///:~
