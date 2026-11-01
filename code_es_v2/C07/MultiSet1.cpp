//: C07:MultiSet1.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Muestra el comportamiento de multiset.
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <set>
using namespace std;

class X {
  char c; // Se usa en la comparación
  int i; // No se usa en la comparación
  // No hacen falta constructor por defecto ni operator=
  X();
  X& operator=(const X&);
  // Normalmente hace falta un constructor de copia (pero
  // aquí sirve la versión sintetizada)
public:
  X(char cc, int ii) : c(cc), i(ii) {}
  // Observe que no hace falta operator==
  friend bool operator<(const X& x, const X& y) {
    return x.c < y.c;
  }
  friend ostream& operator<<(ostream& os, X x) {
    return os << x.c << ":" << x.i;
  }
};

class Xgen {
  static int i;
  // Número de caracteres entre los que elegir:
  enum { SPAN = 6 };
public:
  X operator()() {
    char c = 'A' + rand() % SPAN;
    return X(c, i++);
  }
};

int Xgen::i = 0;

typedef multiset<X> Xmset;
typedef Xmset::const_iterator Xmit;

int main() {
  Xmset mset;
  // Lo llena de objetos X:
  srand(time(0));  // Inicializa la semilla aleatoria
  generate_n(inserter(mset, mset.begin()), 25, Xgen());
  // Inicializa un set normal a partir de mset:
  set<X> unique(mset.begin(), mset.end());
  copy(unique.begin(), unique.end(),
    ostream_iterator<X>(cout, " "));
  cout << "\n----" << endl;
  // Recorre los valores distintos:
  for(set<X>::iterator i = unique.begin();
      i != unique.end(); i++) {
    pair<Xmit, Xmit> p = mset.equal_range(*i);
    copy(p.first,p.second, ostream_iterator<X>(cout, " "));
    cout << endl;
  }
} ///:~
