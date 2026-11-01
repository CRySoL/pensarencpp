//: C03:const_cast.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
int main() {
  const int i = 0;
  int* j = (int*)&i; // Forma desaconsejada
  j  = const_cast<int*>(&i); // Preferida
  // No se puede moldear a otro tipo a la vez:
//! long* l = const_cast<long*>(&i); // Error
  volatile int k = 0;
  int* u = const_cast<int*>(&k);
} ///:~
