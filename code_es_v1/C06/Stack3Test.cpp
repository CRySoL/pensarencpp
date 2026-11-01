//: C06:Stack3Test.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
//{L} Stack3
//{T} Stack3Test.cpp
// Constructores y destructores
#include "Stack3.h"
#include "../require.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
  requireArgs(argc, 1); // Argumento: nombre del fichero
  ifstream in(argv[1]);
  assure(in, argv[1]);
  Stack textlines;
  string line;
  // Leer el fichero y guardar las líneas en la pila:
  while(getline(in, line))
    textlines.push(new string(line));
  // Sacar las líneas de la pila e imprimirlas:
  string* s;
  while((s = (string*)textlines.pop()) != 0) {
    cout << *s << endl;
    delete s; 
  }
} ///:~
