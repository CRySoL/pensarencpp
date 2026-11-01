//: C07:RawStorageIterator.cpp {-bor}
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Muestra el raw_storage_iterator.
//{L} Noisy
#include <iostream>
#include <iterator>
#include <algorithm>
#include "Noisy.h"
using namespace std;

int main() {
  const int QUANTITY = 10;
  // Crea memoria sin inicializar y la moldea al tipo deseado:
  Noisy* np = reinterpret_cast<Noisy*>(
    new char[QUANTITY * sizeof(Noisy)]);
  raw_storage_iterator<Noisy*, Noisy> rsi(np);
  for(int i = 0; i < QUANTITY; i++)
    *rsi++ = Noisy(); // Coloca los objetos en la memoria
  cout << endl;
  copy(np, np + QUANTITY,
    ostream_iterator<Noisy>(cout, " "));
  cout << endl;
  // Llamada explícita al destructor para la limpieza:
  for(int j = 0; j < QUANTITY; j++)
    (&np[j])->~Noisy();
  // Libera la memoria sin inicializar:
  delete reinterpret_cast<char*>(np);
} ///:~
