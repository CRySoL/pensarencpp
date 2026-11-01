//: C06:NumStringGen.h
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Un generador de números aleatorios que produce
// cadenas que representan números de punto flotante.
#ifndef NUMSTRINGGEN_H
#define NUMSTRINGGEN_H
#include <cstdlib>
#include <string>

class NumStringGen {
  const int sz; // Número de dígitos que se generan
public:
  NumStringGen(int ssz = 5) : sz(ssz) {}
  std::string operator()() {
    std::string digits("0123456789");
    const int ndigits = digits.size();
    std::string r(sz, ' ');
    // El primer dígito no debe ser un cero
    r[0] = digits[std::rand() % (ndigits - 1)] + 1;
    // Ahora asignar el resto
    for(int i = 1; i < sz; ++i)
      if(sz >= 3 && i == sz/2)
        r[i] = '.'; // Insertar el punto decimal
      else
        r[i] = digits[std::rand() % ndigits];
    return r;
  }
};
#endif // NUMSTRINGGEN_H ///:~
