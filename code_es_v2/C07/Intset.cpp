//: C07:Intset.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Uso sencillo del set de la STL.
#include <cassert>
#include <set>
using namespace std;

int main() {
  set<int> intset;
  for(int i = 0; i < 25; i++)
    for(int j = 0; j < 10; j++)
      // Intenta insertar duplicados:
      intset.insert(j);
  assert(intset.size() == 10);
} ///:~
