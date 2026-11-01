//: C03:CastFromVoidPointer.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
int main() {
  int i = 99;
  void* vp = &i;
  // No se puede dereferenciar un puntero void:
  // *vp = 3; // Error de compilación
  // Hay que moldearlo de nuevo a int para dereferenciarlo:
  *((int*)vp) = 3;
} ///:~
