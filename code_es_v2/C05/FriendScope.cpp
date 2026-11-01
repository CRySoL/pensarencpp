//: C05:FriendScope.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
#include <iostream>
using namespace std;

class Friendly {
  int i;
public:
  Friendly(int theInt) { i = theInt; }
  friend void f(const Friendly&); // Necesita def. global
  void g() { f(*this); }
};

void h() {
  f(Friendly(1));  // Usa ADL
}

void f(const Friendly& fo) {  // Definición de la amiga
  cout << fo.i << endl;
}

int main() {
  h(); // Imprime 1
  Friendly(2).g(); // Imprime 2
} ///:~
