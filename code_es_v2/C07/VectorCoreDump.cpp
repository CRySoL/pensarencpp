//: C07:VectorCoreDump.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Invalidación de un iterador.
#include <iterator>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> vi(10, 0);
  ostream_iterator<int> out(cout, " ");
  vector<int>::iterator i = vi.begin();
  *i = 47;
  copy(vi.begin(), vi.end(), out);
  cout << endl;
  // Le obliga a mover la memoria (también bastaría
  // con añadir suficientes objetos):
  vi.resize(vi.capacity() + 1);
  // Ahora i apunta a memoria incorrecta:
  *i = 48;  // Violación de acceso
  copy(vi.begin(), vi.end(), out); // vi[0] no cambia
} ///:~
