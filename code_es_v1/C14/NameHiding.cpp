//: C14:NameHiding.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Ocultación de nombres sobrecargados en la herencia
#include <iostream>
#include <string>
using namespace std;

class Base {
public:
  int f() const { 
    cout << "Base::f()\n"; 
    return 1; 
  }
  int f(string) const { return 1; }
  void g() {}
};

class Derived1 : public Base {
public:
  void g() const {}
};

class Derived2 : public Base {
public:
  // Redefinición:
  int f() const { 
    cout << "Derived2::f()\n"; 
    return 2;
  }
};

class Derived3 : public Base {
public:
  // Cambio del tipo de retorno:
  void f() const { cout << "Derived3::f()\n"; }
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
  Derived3 d3;
//!  x = d3.f(); // Versión que devuelve int oculta
  Derived4 d4;
//!  x = d4.f(); // Versión f() oculta
  x = d4.f(1);
} ///:~
