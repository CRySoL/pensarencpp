//: C05:StaticAssert2.cpp {-g++}
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
#include <iostream>
using namespace std;

// Una plantilla y una especialización
template<bool> struct StaticCheck {
  StaticCheck(...);
};

template<> struct StaticCheck<false> {};

// La macro (genera una clase local)
#define STATIC_CHECK(expr, msg) {             \
  class Error_##msg {};                       \
  sizeof((StaticCheck<expr>(Error_##msg()))); \
}

// Detecta las conversiones de estrechamiento
template<class To, class From> To safe_cast(From from) {
  STATIC_CHECK(sizeof(From) <= sizeof(To),
               NarrowingConversion);
  return reinterpret_cast<To>(from);
}

int main() {
  void* p = 0;
  int i = safe_cast<int>(p);
  cout << "int cast okay" << endl;
  //! char c = safe_cast<char>(p);
} ///:~
