//: C04:Strfile.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// E/S de flujos con ficheros;
// La diferencia entre get() y getline().
#include <fstream>
#include <iostream>
#include "../require.h"
using namespace std;

int main() {
  const int SZ = 100; // Tamaño del buffer
  char buf[SZ];
  {
    ifstream in("Strfile.cpp"); // Lectura
    assure(in, "Strfile.cpp"); // Comprueba la apertura
    ofstream out("Strfile.out"); // Escritura
    assure(out, "Strfile.out");
    int i = 1; // Contador de líneas

    // Una forma menos cómoda de leer líneas:
    while(in.get(buf, SZ)) { // Deja el \n en la entrada
      in.get(); // Descarta el siguiente carácter (\n)
      cout << buf << endl; // Hay que añadir el \n
      // Salida a fichero igual que la E/S estándar:
      out << i++ << ": " << buf << endl;
    }
  } // Los destructores cierran in y out

  ifstream in("Strfile.out");
  assure(in, "Strfile.out");
  // Una forma más cómoda de leer líneas:
  while(in.getline(buf, SZ)) { // Quita el \n
    char* cp = buf;
    while(*cp != ':')
      ++cp;
    cp += 2; // Tras ": "
    cout << cp << endl; // Aún hay que añadir el \n
  }
} ///:~
