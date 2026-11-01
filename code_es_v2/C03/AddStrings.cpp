//: C03:AddStrings.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
#include <string>
#include <cassert>
using namespace std;

int main() {
  string s1("This ");
  string s2("That ");
  string s3("The other ");
  // operator+ concatena cadenas
  s1 = s1 + s2;
  assert(s1 == "This That ");
  // Otra forma de concatenar cadenas
  s1 += s3;
  assert(s1 == "This That The other ");
  // Se puede indexar la cadena de la derecha
  s1 += s3 + s3[4] + "ooh lala";
  assert(s1 == "This That The other The other oooh lala");
} ///:~
