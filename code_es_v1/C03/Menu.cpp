//: C03:Menu.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Programa de menú sencillo que muestra
// el uso de "break" y "continue"
#include <iostream>
using namespace std;

int main() {
  char c; // Para guardar la respuesta
  while(true) {
    cout << "MAIN MENU:" << endl;
    cout << "l: left, r: right, q: quit -> ";
    cin >> c;
    if(c == 'q')
      break; // Sale de "while(1)"
    if(c == 'l') {
      cout << "LEFT MENU:" << endl;
      cout << "select a or b: ";
      cin >> c;
      if(c == 'a') {
        cout << "you chose 'a'" << endl;
        continue; // Vuelve al menú principal
      }
      if(c == 'b') {
        cout << "you chose 'b'" << endl;
        continue; // Vuelve al menú principal
      }
      else {
        cout << "you didn't choose a or b!"
             << endl;
        continue; // Vuelve al menú principal
      }
    }
    if(c == 'r') {
      cout << "RIGHT MENU:" << endl;
      cout << "select c or d: ";
      cin >> c;
      if(c == 'c') {
        cout << "you chose 'c'" << endl;
        continue; // Vuelve al menú principal
      }
      if(c == 'd') {
        cout << "you chose 'd'" << endl;
        continue; // Vuelve al menú principal
      }
      else {
        cout << "you didn't choose c or d!" 
             << endl;
        continue; // Vuelve al menú principal
      }
    }
    cout << "you must type l or r or q!" << endl;
  }
  cout << "quitting menu..." << endl;
} ///:~
