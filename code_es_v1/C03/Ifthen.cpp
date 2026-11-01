//: C03:Ifthen.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Ejemplo de las sentencias condicionales if e if-else
#include <iostream>
using namespace std;

int main() {
  int i;
  cout << "type a number and 'Enter'" << endl;
  cin >> i;
  if(i > 5)
    cout << "It's greater than 5" << endl;
  else
    if(i < 5)
      cout << "It's less than 5 " << endl;
    else
      cout << "It's equal to 5 " << endl;

  cout << "type a number and 'Enter'" << endl;
  cin >> i;
  if(i < 10)
    if(i > 5)  // "if" es una sentencia más
      cout << "5 < i < 10" << endl;
    else
      cout << "i <= 5" << endl;
  else // Corresponde a "if(i < 10)"
    cout << "i >= 10" << endl;
} ///:~
