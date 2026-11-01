//: C08:Castaway.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Eliminar la constancia mediante un molde

class Y {
  int i;
public:
  Y();
  void f() const;
};

Y::Y() { i = 0; }

void Y::f() const {
//!  i++; // Error -- método const
  ((Y*)this)->i++; // Correcto: elimina la constancia
  // Mejor: usar la sintaxis de molde explícito de C++:
  (const_cast<Y*>(this))->i++;
}

int main() {
  const Y yy;
  yy.f(); // ¡En realidad lo modifica!
} ///:~
