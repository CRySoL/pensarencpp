//: C10:StaticDestructors.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Destructores de objetos estáticos
#include <fstream>
using namespace std;
ofstream out("statdest.out"); // Fichero de trazas

class Obj {
  char c; // Identificador
public:
  Obj(char cc) : c(cc) {
    out << "Obj::Obj() for " << c << endl;
  }
  ~Obj() {
    out << "Obj::~Obj() for " << c << endl;
  }
};

Obj a('a'); // Global (almacenamiento estático)
// Siempre se llama al constructor y al destructor

void f() {
  static Obj b('b');
}

void g() {
  static Obj c('c');
}

int main() {
  out << "inside main()" << endl;
  f(); // Llama al constructor del b estático
  // No se llama a g()
  out << "leaving main()" << endl;
} ///:~
