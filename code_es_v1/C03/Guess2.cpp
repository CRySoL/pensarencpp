//: C03:Guess2.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// El programa de adivinar con do-while
#include <iostream>
using namespace std;

int main() {
  int secret = 15;
  int guess; // Aquí no hace falta inicializarla
  do {
    cout << "guess the number: ";
    cin >> guess; // Aquí se inicializa
  }   while(guess != secret);
  cout << "You got it!" << endl;
} ///:~
