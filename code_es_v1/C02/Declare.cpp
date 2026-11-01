//: C02:Declare.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Ejemplos de declaración y definición
extern int i; // Declaración sin definición
extern float f(float); // Declaración de función

float b;  // Declaración y definición
float f(float a) {  // Definición
  return a + 1.0;
}

int i; // Definición
int h(int x) { // Declaración y definición
  return x + 1;
}

int main() {
  b = 1.0;
  i = 2;
  f(b);
  h(i);
} ///:~
