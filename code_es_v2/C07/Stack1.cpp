//: C07:Stack1.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Muestra el stack de la STL.
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>
using namespace std;

// Cambie los comentarios de abajo para usar otras versiones.
typedef stack<string> Stack1; // Por defecto: deque<string>
// typedef stack<string, vector<string> > Stack2;
// typedef stack<string, list<string> > Stack3;

int main() {
  ifstream in("Stack1.cpp");
  Stack1 textlines; // Pruebe las distintas versiones
  // Lee el fichero y guarda las líneas en la pila:
  string line;
  while(getline(in, line))
    textlines.push(line + "\n");
  // Imprime las líneas de la pila y las saca:
  while(!textlines.empty()) {
    cout << textlines.top();
    textlines.pop();
  }
} ///:~
