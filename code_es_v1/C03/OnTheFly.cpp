//: C03:OnTheFly.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Definición de variables al vuelo
#include <iostream>
using namespace std;

int main() {
  //..
  { // Empieza un nuevo ámbito
    int q = 0; // C exige las definiciones aquí
    //..
    // Definición en el punto de uso:
    for(int i = 0; i < 100; i++) { 
      q++; // q viene de un ámbito mayor
      // Definición al final del ámbito:
      int p = 12; 
    }
    int p = 1;  // Una p distinta
  } // Fin del ámbito que contiene q y la p exterior
  cout << "Type characters:" << endl;
  while(char c = cin.get() != 'q') {
    cout << c << " wasn't it" << endl;
    if(char x = c == 'a' || c == 'b')
      cout << "You typed a or b" << endl;
    else
      cout << "You typed " << x << endl;
  }
  cout << "Type A, B, or C" << endl;
  switch(int i = cin.get()) {
    case 'A': cout << "Snap" << endl; break;
    case 'B': cout << "Crackle" << endl; break;
    case 'C': cout << "Pop" << endl; break;
    default: cout << "Not A, B or C!" << endl;
  }
} ///:~
