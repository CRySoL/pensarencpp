//: C11:NoCopyConstruction.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Cómo impedir la construcción por copia

class NoCC {
  int i;
  NoCC(const NoCC&); // Sin definición
public:
  NoCC(int ii = 0) : i(ii) {}
};

void f(NoCC);

int main() {
  NoCC n;
//! f(n); // Error: llama al constructor de copia
//! NoCC n2 = n; // Error: llama al constructor de copia
//! NoCC n3(n); // Error: llama al constructor de copia
} ///:~
