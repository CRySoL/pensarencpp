//: C03:Charlist.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Muestra todos los caracteres ASCII
// Ilustra el uso de "for"
#include <iostream>
using namespace std;

int main() {
  for(int i = 0; i < 128; i = i + 1)
    if (i != 26)  // Borra la pantalla en terminales ANSI
      cout << " value: " << i 
           << " character: " 
           << char(i) // Conversión de tipo
           << endl;
} ///:~
