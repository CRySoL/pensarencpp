//: C07:Stack2.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Conversión de una lista en una pila.
#include <iostream>
#include <fstream>
#include <stack>
#include <list>
#include <string>
#include <cstddef>
using namespace std;

// Espera una pila:
template<class Stk>
void stackOut(Stk& s, ostream& os = cout) {
  while(!s.empty()) {
    os << s.top() << "\n";
    s.pop();
  }
}

class Line {
  string line; // Sin los espacios iniciales
  size_t lspaces; // Número de espacios iniciales
public:
  Line(string s) : line(s) {
    lspaces = line.find_first_not_of(' ');
    if(lspaces == string::npos)
      lspaces = 0;
    line = line.substr(lspaces);
  }
  friend ostream& operator<<(ostream& os, const Line& l) {
    for(size_t i = 0; i < l.lspaces; i++)
      os << ' ';
    return os << l.line;
  }
  // Aquí, otras funciones...
};

int main() {
  ifstream in("Stack2.cpp");
  list<Line> lines;
  // Lee el fichero y guarda las líneas en la lista:
  string s;
  while(getline(in, s))
    lines.push_front(s);
  // Convierte la lista en una pila para imprimirla:
  stack<Line, list<Line> > stk(lines);
  stackOut(stk);
} ///:~
