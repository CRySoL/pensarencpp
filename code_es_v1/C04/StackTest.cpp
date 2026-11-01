//: C04:StackTest.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
//{L} Stack
//{T} StackTest.cpp
// Prueba de la lista enlazada con anidamiento
#include "Stack.h"
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
  textlines.initialize();
  string line;
  // Lee el fichero y guarda las líneas en la Stack:
  while(getline(in, line))
    textlines.push(new string(line));
  // Saca las líneas de la Stack y las imprime:
  string* s;
  while((s = (string*)textlines.pop()) != 0) {
    cout << *s << endl;
    delete s; 
  }
  textlines.cleanup();
} ///:~
