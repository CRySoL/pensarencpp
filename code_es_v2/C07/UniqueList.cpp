//: C07:UniqueList.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Prueba de la función unique() de list.
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

int a[] = { 1, 3, 1, 4, 1, 5, 1, 6, 1 };
const int ASZ = sizeof a / sizeof *a;

int main() {
  // Para la salida:
  ostream_iterator<int> out(cout, " ");
  list<int> li(a, a + ASZ);
  li.unique();
  // ¡Vaya! No se ha eliminado ningún duplicado:
  copy(li.begin(), li.end(), out);
  cout << endl;
  // Primero hay que ordenarla:
  li.sort();
  copy(li.begin(), li.end(), out);
  cout << endl;
  // Ahora unique() sí tendrá efecto:
  li.unique();
  copy(li.begin(), li.end(), out);
  cout << endl;
} ///:~
