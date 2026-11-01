//: C15:UnAbstract.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Los destructores virtuales puros
// parecen comportarse de forma extraña

class AbstractBase {
public:
  virtual ~AbstractBase() = 0;
};

AbstractBase::~AbstractBase() {}

class Derived : public AbstractBase {};
// ¿No hace falta redefinir el destructor?

int main() { Derived d; } ///:~
