//: C07:AssociativeBasics.cpp {-bor}
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Operaciones básicas con set y map.
//{L} Noisy
#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include "Noisy.h"
using namespace std;

int main() {
  Noisy na[7];
  // Añade elementos mediante el constructor:
  set<Noisy> ns(na, na + sizeof na/sizeof(Noisy));
  Noisy n;
  ns.insert(n); // Inserción normal
  cout << endl;
  // Comprueba si pertenece al set:
  cout << "ns.count(n)= " << ns.count(n) << endl;
  if(ns.find(n) != ns.end())
    cout << "n(" << n << ") found in ns" << endl;
  // Imprime los elementos:
  copy(ns.begin(), ns.end(),
    ostream_iterator<Noisy>(cout, " "));
  cout << endl;
  cout << "\n-----------" << endl;
  map<int, Noisy> nm;
  for(int i = 0; i < 10; i++)
    nm[i]; // Crea los pares automáticamente
  cout << "\n-----------" << endl;
  for(size_t j = 0; j < nm.size(); j++)
    cout << "nm[" << j <<"] = " << nm[j] << endl;
  cout << "\n-----------" << endl;
  nm[10] = n;
  cout << "\n-----------" << endl;
  nm.insert(make_pair(47, n));
  cout << "\n-----------" << endl;
  cout << "\n nm.count(10)= " << nm.count(10) << endl;
  cout << "nm.count(11)= " << nm.count(11) << endl;
  map<int, Noisy>::iterator it = nm.find(6);
  if(it != nm.end())
    cout << "value:" << (*it).second
         << " found in nm at location 6" << endl;
  for(it = nm.begin(); it != nm.end(); it++)
    cout << (*it).first << ":" << (*it).second << ", ";
  cout << "\n-----------" << endl;
} ///:~
