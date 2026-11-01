//: C08:ConstPointer.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Puntero constante como argumento y retorno

void t(int*) {}

void u(const int* cip) {
//!  *cip = 2; // Ilegal -- modifica el valor
  int i = *cip; // Correcto -- copia el valor
//!  int* ip2 = cip; // Ilegal: no const
}

const char* v() {
  // Devuelve la dirección de un array estático de char:
  return "result of function v()";
}

const int* const w() {
  static int i;
  return &i;
}

int main() {
  int x = 0;
  int* ip = &x;
  const int* cip = &x;
  t(ip);  // Correcto
//!  t(cip); // Incorrecto
  u(ip);  // Correcto
  u(cip); // También correcto
//!  char* cp = v(); // Incorrecto
  const char* ccp = v(); // Correcto
//!  int* ip2 = w(); // Incorrecto
  const int* const ccip = w(); // Correcto
  const int* cip2 = w(); // Correcto
//!  *w() = 1; // Incorrecto
} ///:~
