//: C12:TypeConversionAmbiguity.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
class Orange; // Declaración de clase

class Apple {
public:
  operator Orange() const; // Convierte Apple en Orange
};

class Orange {
public:
  Orange(Apple); // Convierte Apple en Orange
};

void f(Orange) {}

int main() {
  Apple a;
//! f(a); // Error: conversión ambigua
} ///:~
