//: C09:ErrTest.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
//{T} ErrTest.cpp
// Prueba de require.h
#include "../require.h"
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
  int i = 1;
  require(i, "value must be nonzero");
  requireArgs(argc, 1);
  requireMinArgs(argc, 1);
  ifstream in(argv[1]);
  assure(in, argv[1]); // Usa el nombre del fichero
  ifstream nofile("nofile.xxx");
  // Falla:
//!  assure(nofile); // El argumento por defecto
  ofstream out("tmp.txt");
  assure(out);
} ///:~
