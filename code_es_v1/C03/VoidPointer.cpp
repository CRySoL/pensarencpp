//: C03:VoidPointer.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
int main() {
  void* vp;
  char c;
  int i;
  float f;
  double d;
  // Se puede asignar la dirección de CUALQUIER
  // tipo a un puntero void:
  vp = &c;
  vp = &i;
  vp = &f;
  vp = &d;
} ///:~
