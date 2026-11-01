//: C11:Reference.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Referencias sencillas en C++

int* f(int* x) {
  (*x)++;
  return x; // Seguro, x está fuera de este ámbito
}

int& g(int& x) {
  x++; // El mismo efecto que en f()
  return x; // Seguro, fuera de este ámbito
}

int& h() {
  int q;
//!  return q;  // Error
  static int x;
  return x; // Seguro, x vive fuera de este ámbito
}

int main() {
  int a = 0;
  f(&a); // Feo (pero explícito)
  g(a);  // Limpio (pero oculto)
} ///:~
