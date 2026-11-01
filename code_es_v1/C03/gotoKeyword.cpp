//: C03:gotoKeyword.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// C++ admite el tristemente célebre goto
#include <iostream>
using namespace std;

int main() {
  long val = 0;
  for(int i = 1; i < 1000; i++) {
    for(int j = 1; j < 100; j += 10) {
      val = i * j;
      if(val > 47000)
        goto bottom; 
        // Un break solo saldría al 'for' exterior
    }
  }
  bottom: // Una etiqueta
  cout << val << endl;
} ///:~
