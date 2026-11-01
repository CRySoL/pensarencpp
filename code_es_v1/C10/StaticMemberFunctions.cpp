//: C10:StaticMemberFunctions.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
class X {
  int i;
  static int j;
public:
  X(int ii = 0) : i(ii) {
     // Un método no estático puede acceder a
     // métodos o atributos estáticos:
    j = i;
  }
  int val() const { return i; }
  static int incr() {
    //! i++; // Error: un método estático no
    // puede acceder a atributos no estáticos
    return ++j;
  }
  static int f() {
    //! val(); // Error: un método estático no
    // puede acceder a métodos no estáticos
    return incr(); // Correcto: llama a uno estático
  }
};

int X::j = 0;

int main() {
  X x;
  X* xp = &x;
  x.f();
  xp->f();
  X::f(); // Solo funciona con miembros estáticos
} ///:~
