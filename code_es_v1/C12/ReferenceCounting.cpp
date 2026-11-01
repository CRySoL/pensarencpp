//: C12:ReferenceCounting.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Cuenta de referencias, copia en escritura
#include "../require.h"
#include <string>
#include <iostream>
using namespace std;

class Dog {
  string nm;
  int refcount;
  Dog(const string& name) 
    : nm(name), refcount(1) {
    cout << "Creating Dog: " << *this << endl;
  }
  // Impide la asignación:
  Dog& operator=(const Dog& rv);
public:
  // Los Dog solo se pueden crear en el montículo:
  static Dog* make(const string& name) {
    return new Dog(name);
  }
  Dog(const Dog& d) 
    : nm(d.nm + " copy"), refcount(1) {
    cout << "Dog copy-constructor: " 
         << *this << endl;
  }
  ~Dog() { 
    cout << "Deleting Dog: " << *this << endl;
  }
  void attach() { 
    ++refcount;
    cout << "Attached Dog: " << *this << endl;
  }
  void detach() {
    require(refcount != 0);
    cout << "Detaching Dog: " << *this << endl;
    // Destruye el objeto si nadie lo está usando:
    if(--refcount == 0) delete this;
  }
  // Copia este Dog si hace falta.
  // Llámela antes de modificar el Dog y asigne
  // el puntero resultante a su Dog*.
  Dog* unalias() {
    cout << "Unaliasing Dog: " << *this << endl;
    // Si no está solapado, no lo duplica:
    if(refcount == 1) return this;
    --refcount;
    // Usa el constructor de copia para duplicarlo:
    return new Dog(*this);
  }
  void rename(const string& newName) {
    nm = newName;
    cout << "Dog renamed to: " << *this << endl;
  }
  friend ostream&
  operator<<(ostream& os, const Dog& d) {
    return os << "[" << d.nm << "], rc = " 
      << d.refcount;
  }
};

class DogHouse {
  Dog* p;
  string houseName;
public:
  DogHouse(Dog* dog, const string& house)
   : p(dog), houseName(house) {
    cout << "Created DogHouse: "<< *this << endl;
  }
  DogHouse(const DogHouse& dh)
    : p(dh.p),
      houseName("copy-constructed " + 
        dh.houseName) {
    p->attach();
    cout << "DogHouse copy-constructor: "
         << *this << endl;
  }
  DogHouse& operator=(const DogHouse& dh) {
    // Comprueba la autoasignación:
    if(&dh != this) {
      houseName = dh.houseName + " assigned";
      // Primero limpia lo que está usando:
      p->detach();
      p = dh.p; // Como el constructor de copia
      p->attach();
    }
    cout << "DogHouse operator= : "
         << *this << endl;
    return *this;
  }
  // Decrementa la cuenta; destruye si hace falta
  ~DogHouse() {
    cout << "DogHouse destructor: " 
         << *this << endl;
    p->detach(); 
  }
  void renameHouse(const string& newName) {
    houseName = newName;
  }
  void unalias() { p = p->unalias(); }
  // Copia en escritura. Siempre que se modifique
  // el contenido del puntero, primero hay que
  // deshacer el solapamiento:
  void renameDog(const string& newName) {
    unalias();
    p->rename(newName);
  }
  // ... o cuando se da acceso a otro:
  Dog* getDog() {
    unalias();
    return p; 
  }
  friend ostream&
  operator<<(ostream& os, const DogHouse& dh) {
    return os << "[" << dh.houseName 
      << "] contains " << *dh.p;
  }
}; 

int main() {
  DogHouse 
    fidos(Dog::make("Fido"), "FidoHouse"),
    spots(Dog::make("Spot"), "SpotHouse");
  cout << "Entering copy-construction" << endl;
  DogHouse bobs(fidos);
  cout << "After copy-constructing bobs" << endl;
  cout << "fidos:" << fidos << endl;
  cout << "spots:" << spots << endl;
  cout << "bobs:" << bobs << endl;
  cout << "Entering spots = fidos" << endl;
  spots = fidos;
  cout << "After spots = fidos" << endl;
  cout << "spots:" << spots << endl;
  cout << "Entering self-assignment" << endl;
  bobs = bobs;
  cout << "After self-assignment" << endl;
  cout << "bobs:" << bobs << endl;
  // Comente las líneas siguientes:
  cout << "Entering rename(\"Bob\")" << endl;
  bobs.getDog()->rename("Bob");
  cout << "After rename(\"Bob\")" << endl;
} ///:~
