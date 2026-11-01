//: C03:Rparse.h
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
#ifndef RPARSE_H
#define RPARSE_H
#include <cstddef>
#include <string>
#include <vector>
#include "../TestSuite/Test.h"
using std::size_t;
using std::string;
using std::vector;

class RparseTest : public TestSuite::Test {
  // Para guardar las palabras:
  vector<string> strings;
public:
  void parseForData() {
    // Los caracteres ';' serán los delimitadores
    string s("now.;sense;make;to;going;is;This");
    // El último elemento de la cadena:
    int last = s.size();
    // El comienzo de la palabra actual:
    size_t current = s.rfind(';');
    // Recorre la cadena hacia atrás:
    while(current != string::npos) {
      // Mete cada palabra en el vector.
      // current se incrementa antes de copiar
      // para no copiar el delimitador:
      ++current;
      strings.push_back(s.substr(current, last - current));
      // Retrocede sobre el delimitador encontrado
      // y pone last al final de la siguiente palabra:
      current -= 2;
      last = current + 1;
      // Busca el siguiente delimitador:
      current = s.rfind(';', current);
    }
    // Recoge la primera palabra, que no va
    // precedida de un delimitador:
    strings.push_back(s.substr(0, last));
  }
  void testData() {
    // Las comprueba en el nuevo orden:
    test_(strings[0] == "This");
    test_(strings[1] == "is");
    test_(strings[2] == "going");
    test_(strings[3] == "to");
    test_(strings[4] == "make");
    test_(strings[5] == "sense");
    test_(strings[6] == "now.");
    string sentence;
    for(size_t i = 0; i < strings.size() - 1; i++)
      sentence += strings[i] += " ";
    // Añade a mano la última palabra, sin espacio de más:
    sentence += strings[strings.size() - 1];
    test_(sentence == "This is going to make sense now.");
  }
  void run() {
    parseForData();
    testData();
  }
};
#endif // RPARSE_H ///:~
