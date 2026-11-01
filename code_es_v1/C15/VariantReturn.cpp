//: C15:VariantReturn.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Retorno de un puntero o una referencia a un tipo
// derivado al redefinir
#include <iostream>
#include <string>
using namespace std;

class PetFood {
public:
  virtual string foodType() const = 0;
};

class Pet {
public:
  virtual string type() const = 0;
  virtual PetFood* eats() = 0;
};

class Bird : public Pet {
public:
  string type() const { return "Bird"; }
  class BirdFood : public PetFood {
  public:
    string foodType() const { 
      return "Bird food"; 
    }
  };
  // Upcast al tipo base:
  PetFood* eats() { return &bf; }
private:
  BirdFood bf;
};

class Cat : public Pet {
public:
  string type() const { return "Cat"; }
  class CatFood : public PetFood {
  public:
    string foodType() const { return "Birds"; }
  };
  // En su lugar, devuelve el tipo exacto:
  CatFood* eats() { return &cf; }
private:
  CatFood cf;
};

int main() {
  Bird b; 
  Cat c;
  Pet* p[] = { &b, &c, };
  for(int i = 0; i < sizeof p / sizeof *p; i++)
    cout << p[i]->type() << " eats "
         << p[i]->eats()->foodType() << endl;
  // Puede devolver el tipo exacto:
  Cat::CatFood* cf = c.eats();
  Bird::BirdFood* bf;
  // No puede devolver el tipo exacto:
//!  bf = b.eats();
  // Hay que hacer downcast:
  bf = dynamic_cast<Bird::BirdFood*>(b.eats());
} ///:~
