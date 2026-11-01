//: C16:AutoCounter.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
#ifndef AUTOCOUNTER_H
#define AUTOCOUNTER_H
#include "../require.h"
#include <iostream>
#include <set> // Contenedor de la librería estándar de C++
#include <string>

class AutoCounter {
  static int count;
  int id;
  class CleanupCheck {
    std::set<AutoCounter*> trace;
  public:
    void add(AutoCounter* ap) {
      trace.insert(ap);
    }
    void remove(AutoCounter* ap) {
      require(trace.erase(ap) == 1,
        "Attempt to delete AutoCounter twice");
    }
    ~CleanupCheck() {
      std::cout << "~CleanupCheck()"<< std::endl;
      require(trace.size() == 0,
       "All AutoCounter objects not cleaned up");
    }
  };
  static CleanupCheck verifier;
  AutoCounter() : id(count++) {
    verifier.add(this); // Se registra a sí mismo
    std::cout << "created[" << id << "]" 
              << std::endl;
  }
  // Impide la asignación y la construcción por copia:
  AutoCounter(const AutoCounter&);
  void operator=(const AutoCounter&);
public:
  // Los objetos solo se pueden crear con esto:
  static AutoCounter* create() { 
    return new AutoCounter();
  }
  ~AutoCounter() {
    std::cout << "destroying[" << id 
              << "]" << std::endl;
    verifier.remove(this);
  }
  // Imprime tanto objetos como punteros:
  friend std::ostream& operator<<(
    std::ostream& os, const AutoCounter& ac){
    return os << "AutoCounter " << ac.id;
  }
  friend std::ostream& operator<<(
    std::ostream& os, const AutoCounter* ac){
    return os << "AutoCounter " << ac->id;
  }
}; 
#endif // AUTOCOUNTER_H ///:~
