//: C12:TypeConversionFanout.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
class Orange {};
class Pear {};

class Apple {
public:
  operator Orange() const;
  operator Pear() const;
};

// eat() sobrecargada:
void eat(Orange);
void eat(Pear);

int main() {
  Apple c;
//! eat(c);
  // Error: ¿Apple -> Orange o Apple -> Pear?
} ///:~
