//: C10:StaticObjectArrays.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Arrays estáticos de objetos de clase
class X {
  int i;
public:
  X(int ii) : i(ii) {}
};

class Stat {
  // Esto no funciona, aunque sería deseable:
//!  static const X x(100);
  // Los objetos estáticos de clase, const o no,
  // se deben inicializar fuera de la clase:
  static X x2;
  static X xTable2[];
  static const X x3;
  static const X xTable3[];
};

X Stat::x2(100);

X Stat::xTable2[] = {
  X(1), X(2), X(3), X(4)
};

const X Stat::x3(100);

const X Stat::xTable3[] = {
  X(1), X(2), X(3), X(4)
};

int main() { Stat v; } ///:~
