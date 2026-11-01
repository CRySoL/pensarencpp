//: C10:Initializer.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Técnica de inicialización estática
#ifndef INITIALIZER_H
#define INITIALIZER_H
#include <iostream>
extern int x; // Declaraciones, no definiciones
extern int y;

class Initializer {
  static int initCount;
public:
  Initializer() {
    std::cout << "Initializer()" << std::endl;
    // Inicializa solo la primera vez
    if(initCount++ == 0) {
      std::cout << "performing initialization"
                << std::endl;
      x = 100;
      y = 200;
    }
  }
  ~Initializer() {
    std::cout << "~Initializer()" << std::endl;
    // Limpia solo la última vez
    if(--initCount == 0) {
      std::cout << "performing cleanup" 
                << std::endl;
      // Aquí, la limpieza que haga falta
    }
  }
};

// Lo siguiente crea un objeto en cada fichero
// que incluya Initializer.h, pero ese objeto
// solo es visible dentro de ese fichero:
static Initializer init;
#endif // INITIALIZER_H ///:~
