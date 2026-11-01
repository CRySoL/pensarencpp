//: C15:StaticHierarchyNavigation.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Navegación por jerarquías de clases con static_cast
#include <iostream>
#include <typeinfo>
using namespace std;

class Shape { public: virtual ~Shape() {}; };
class Circle : public Shape {};
class Square : public Shape {};
class Other {};

int main() {
  Circle c;
  Shape* s = &c; // Upcast: normal y correcto
  // Más explícito, pero innecesario:
  s = static_cast<Shape*>(&c);
  // (Como el upcasting es una operación tan segura
  // y habitual, el molde solo estorba)
  Circle* cp = 0;
  Square* sp = 0;
  // La navegación estática por jerarquías de clases
  // necesita información de tipo adicional:
  if(typeid(s) == typeid(cp)) // RTTI de C++
    cp = static_cast<Circle*>(s);
  if(typeid(s) == typeid(sp))
    sp = static_cast<Square*>(s);
  if(cp != 0)
    cout << "It's a circle!" << endl;
  if(sp != 0)
    cout << "It's a square!" << endl;
  // La navegación estática es SOLO un truco de
  // eficiencia; dynamic_cast siempre es más seguro.
  // Sin embargo, esto:
  // Other* op = static_cast<Other*>(s);
  // produce oportunamente un mensaje de error, y esto:
  Other* op2 = (Other*)s;
  // no lo produce
} ///:~
