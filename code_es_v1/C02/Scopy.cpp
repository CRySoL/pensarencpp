//: C02:Scopy.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Copia un fichero en otro, línea a línea
#include <string>
#include <fstream>
using namespace std;

int main() {
  ifstream in("Scopy.cpp"); // Abre para lectura
  ofstream out("Scopy2.cpp"); // Abre para escritura
  string s;
  while(getline(in, s)) // Descarta el salto de línea
    out << s << "\n"; // ... hay que volver a añadirlo
} ///:~
