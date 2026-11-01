//: C09:EvaluationOrder.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Orden de evaluación de las funciones inline

class Forward {
  int i;
public:
  Forward() : i(0) {}
  // Llamada a una función no declarada:
  int f() const { return g() + 1; }
  int g() const { return i; }
};

int main() {
  Forward frwd;
  frwd.f();
} ///:~
