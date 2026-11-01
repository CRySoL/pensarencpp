//: C03:StrSize.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
#include <string>
#include <iostream>
using namespace std;

int main() {
  string bigNews("I saw Elvis in a UFO. ");
  cout << bigNews << endl;
  // ¿Cuántos datos hay realmente?
  cout << "Size = " << bigNews.size() << endl;
  // ¿Cuánto cabe sin reservar más memoria?
  cout << "Capacity = " << bigNews.capacity() << endl;
  // Inserta esta cadena en bigNews justo
  // antes de bigNews[1]:
  bigNews.insert(1, " thought I");
  cout << bigNews << endl;
  cout << "Size = " << bigNews.size() << endl;
  cout << "Capacity = " << bigNews.capacity() << endl;
  // Se asegura de que habrá todo este espacio
  bigNews.reserve(500);
  // Añade esto al final de la cadena:
  bigNews.append("I've been working too hard.");
  cout << bigNews << endl;
  cout << "Size = " << bigNews.size() << endl;
  cout << "Capacity = " << bigNews.capacity() << endl;
} ///:~
