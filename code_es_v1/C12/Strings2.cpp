//: C12:Strings2.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Con conversión automática de tipo
#include "../require.h"
#include <cstring>
#include <cstdlib>
#include <string>
using namespace std;

class Stringc {
  string s;
public:
  Stringc(const string& str = "") : s(str) {}
  operator const char*() const { 
    return s.c_str(); 
  }
};

int main() {
  Stringc s1("hello"), s2("there");
  strcmp(s1, s2); // Función de C estándar
  strspn(s1, s2); // ¡Cualquier función de cadenas!
} ///:~
