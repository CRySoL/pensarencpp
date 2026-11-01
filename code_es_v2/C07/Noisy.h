//: C07:Noisy.h
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Una clase que registra la actividad de los objetos.
#ifndef NOISY_H
#define NOISY_H
#include <iostream>
using std::endl;
using std::cout;
using std::ostream;

class Noisy {
  static long create, assign, copycons, destroy;
  long id;
public:
  Noisy() : id(create++) {
    cout << "d[" << id << "]" << endl;
  }
  Noisy(const Noisy& rv) : id(rv.id) {
    cout << "c[" << id << "]" << endl;
    ++copycons;
  }
  Noisy& operator=(const Noisy& rv) {
    cout << "(" << id << ")=[" << rv.id << "]" << endl;
    id = rv.id;
    ++assign;
    return *this;
  }
  friend bool operator<(const Noisy& lv, const Noisy& rv) {
    return lv.id < rv.id;
  }
  friend bool operator==(const Noisy& lv,const Noisy& rv) {
    return lv.id == rv.id;
  }
  ~Noisy() {
    cout << "~[" << id << "]" << endl;
    ++destroy;
  }
  friend ostream& operator<<(ostream& os, const Noisy& n) {
    return os << n.id;
  }
  friend class NoisyReport;
};

struct NoisyGen {
  Noisy operator()() { return Noisy(); }
};

// Un Único (Singleton). Informa automáticamente de las
// estadísticas cuando termina el programa:
class NoisyReport {
  static NoisyReport nr;
  NoisyReport() {} // Constructor privado
  NoisyReport & operator=(NoisyReport &);  // No permitido
  NoisyReport(const NoisyReport&);         // No permitido
public:
  ~NoisyReport() {
    cout << "\n-------------------\n"
         << "Noisy creations: " << Noisy::create
         << "\nCopy-Constructions: " << Noisy::copycons
         << "\nAssignments: " << Noisy::assign
         << "\nDestructions: " << Noisy::destroy << endl;
  }
};
#endif // NOISY_H ///:~
