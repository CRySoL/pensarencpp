//: C15:PureVirtualDefinitions.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Definiciones de virtuales puras en la base
#include <iostream>
using namespace std;

class Pet {
public:
  virtual void speak() const = 0;
  virtual void eat() const = 0;
  // Ilegal: definiciones inline de virtuales puras:
  //!  virtual void sleep() const = 0 {}
};

// Correcto, no está definida inline
void Pet::eat() const {
  cout << "Pet::eat()" << endl;
}

void Pet::speak() const { 
  cout << "Pet::speak()" << endl;
}

class Dog : public Pet {
public:
  // Usa el código común de Pet:
  void speak() const { Pet::speak(); }
  void eat() const { Pet::eat(); }
};

int main() {
  Dog simba;  // El perro de Richard
  simba.speak();
  simba.eat();
} ///:~
