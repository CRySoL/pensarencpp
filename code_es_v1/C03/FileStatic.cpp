//: C03:FileStatic.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Ejemplo de ámbito de fichero. Compilar y
// enlazar este fichero con FileStatic2.cpp
// provoca un error del enlazador

// Ámbito de fichero: solo disponible en este fichero:
static int fs; 

int main() {
  fs = 1;
} ///:~
