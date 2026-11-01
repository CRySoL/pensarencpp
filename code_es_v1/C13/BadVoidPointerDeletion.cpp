//: C13:BadVoidPointerDeletion.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Borrar punteros void puede provocar fugas de memoria
#include <iostream>
using namespace std;

class Object {
  void* data; // Algo de memoria
  const int size;
  const char id;
public:
  Object(int sz, char c) : size(sz), id(c) {
    data = new char[size];
    cout << "Constructing object " << id 
         << ", size = " << size << endl;
  }
  ~Object() { 
    cout << "Destructing object " << id << endl;
    delete []data; // Correcto, solo libera memoria;
    // no hace falta llamar a destructores
  }
};

int main() {
  Object* a = new Object(40, 'a');
  delete a;
  void* b = new Object(40, 'b');
  delete b;
} ///:~
