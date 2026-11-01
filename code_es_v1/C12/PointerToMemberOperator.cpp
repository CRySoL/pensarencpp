//: C12:PointerToMemberOperator.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
#include <iostream>
using namespace std;

class Dog {
public:
  int run(int i) const { 
    cout << "run\n";  
    return i; 
  }
  int eat(int i) const { 
     cout << "eat\n";  
     return i; 
  }
  int sleep(int i) const { 
    cout << "ZZZ\n"; 
    return i; 
  }
  typedef int (Dog::*PMF)(int) const;
  // operator->* debe devolver un objeto
  // que tenga un operator():
  class FunctionObject {
    Dog* ptr;
    PMF pmem;
  public:
    // Guarda el puntero al objeto y el puntero a miembro
    FunctionObject(Dog* wp, PMF pmf) 
      : ptr(wp), pmem(pmf) { 
      cout << "FunctionObject constructor\n";
    }
    // Hace la llamada con el puntero al objeto
    // y el puntero a miembro
    int operator()(int i) const {
      cout << "FunctionObject::operator()\n";
      return (ptr->*pmem)(i); // Hace la llamada
    }
  };
  FunctionObject operator->*(PMF pmf) { 
    cout << "operator->*" << endl;
    return FunctionObject(this, pmf);
  }
};
 
int main() {
  Dog w;
  Dog::PMF pmf = &Dog::run;
  cout << (w->*pmf)(1) << endl;
  pmf = &Dog::sleep;
  cout << (w->*pmf)(2) << endl;
  pmf = &Dog::eat;
  cout << (w->*pmf)(3) << endl;
} ///:~
