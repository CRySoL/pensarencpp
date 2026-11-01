//: C03:Compare2.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Muestra la versión sobrecargada de compare().
#include <cassert>
#include <string>
using namespace std;

int main() {
  string first("This is a day that will live in infamy");
  string second("I don't believe that this is what "
                "I signed up for");
  // Compara "his is" en las dos cadenas:
  assert(first.compare(1, 7, second, 22, 7) == 0);
  // Compara "his is a" con "his is w":
  assert(first.compare(1, 9, second, 22, 9) < 0);
} ///:~
