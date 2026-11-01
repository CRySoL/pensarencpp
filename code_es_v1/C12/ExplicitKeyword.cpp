//: C12:ExplicitKeyword.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Uso de la palabra reservada "explicit"
class One {
public:
  One() {}
};

class Two {
public:
  explicit Two(const One&) {}
};

void f(Two) {}

int main() {
  One one;
//!  f(one); // No se permite la conversión automática
  f(Two(one)); // Correcto: el usuario hace la conversión
} ///:~
