//: C03:Enum.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Seguimiento de formas

enum ShapeType {
  circle,
  square,
  rectangle
};  // Debe terminar en punto y coma, como una struct

int main() {
  ShapeType shape = circle;
  // Aquí van otras tareas....
  // Ahora se hace algo según la forma que sea:
  switch(shape) {
    case circle:  /* código del círculo */ break;
    case square:  /* código del cuadrado */ break;
    case rectangle:  /* código del rectángulo */ break;
  }
} ///:~
