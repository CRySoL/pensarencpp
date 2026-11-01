//: C15:NameHiding2.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Las funciones virtuales restringen la sobrecarga
#include <iostream>
#include <string>
using namespace std;

class Base {
public:
  virtual int f() const { 
    cout << "Base::f()\n"; 
    return 1; 
  }
  virtual void f(string) const {}
  virtual void g() const {}
};

class Derived1 : public Base {
public:
  void g() const {}
};

class Derived2 : public Base {
public:
  // Redefinición de una función virtual:
  int f() const { 
    cout << "Derived2::f()\n"; 
    return 2;
  }
};

class Derived3 : public Base {
public:
  // No se puede cambiar el tipo de retorno:
  //! void f() const{ cout << "Derived3::f()\n";}
};

class Derived4 : public Base {
public:
  // Cambio de la lista de argumentos:
  int f(int) const { 
    cout << "Derived4::f()\n"; 
    return 4; 
  }
};

int main() {
  string s("hello");
  Derived1 d1;
  int x = d1.f();
  d1.f(s);
  Derived2 d2;
  x = d2.f();
//!  d2.f(s); // Versión string oculta
  Derived4 d4;
  x = d4.f(1);
//!  x = d4.f(); // Versión f() oculta
//!  d4.f(s); // Versión string oculta
  Base& br = d4; // Upcast
//!  br.f(1); // Versión derivada no disponible
  br.f(); // Versión base disponible
  br.f(s); // Versión base disponible
} ///:~
