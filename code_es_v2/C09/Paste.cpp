//: C09:Paste.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
//{L} Vendor
// Arreglar un desaguisado con HM.
#include <iostream>
#include "Vendor.h"
using namespace std;

class MyBase { // Repara la interfaz de Vendor
public:
  virtual void v() const = 0;
  virtual void f() const = 0;
  // Nueva función de la interfaz:
  virtual void g() const = 0;
  virtual ~MyBase() { cout << "~MyBase()" << endl; }
};

class Paste1 : public MyBase, public Vendor1 {
public:
  void v() const {
    cout << "Paste1::v()" << endl;
    Vendor1::v();
  }
  void f() const {
    cout << "Paste1::f()" << endl;
    Vendor1::f();
  }
  void g() const { cout << "Paste1::g()" << endl; }
  ~Paste1() { cout << "~Paste1()" << endl; }
};

int main() {
  Paste1& p1p = *new Paste1;
  MyBase& mp = p1p; // Upcast
  cout << "calling f()" << endl;
  mp.f();  // Comportamiento correcto
  cout << "calling g()" << endl;
  mp.g(); // Comportamiento nuevo
  cout << "calling A(p1p)" << endl;
  A(p1p); // El comportamiento de siempre
  cout << "calling B(p1p)" << endl;
  B(p1p);  // El comportamiento de siempre
  cout << "delete mp" << endl;
  // Borrado de un objeto del montículo mediante una referencia:
  delete &mp; // Comportamiento correcto
} ///:~
