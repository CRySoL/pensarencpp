//: C10:Header2.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
#ifndef HEADER2_H
#define HEADER2_H
#include "Header1.h"
// Añade más nombres a MyLib
namespace MyLib { // ¡NO es una redefinición!
  extern int y;
  void g();
  // ...
} 

#endif // HEADER2_H ///:~
