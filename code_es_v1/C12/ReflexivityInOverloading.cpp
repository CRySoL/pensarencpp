//: C12:ReflexivityInOverloading.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
class Number {
  int i;
public:
  Number(int ii = 0) : i(ii) {}
  const Number
  operator+(const Number& n) const {
    return Number(i + n.i);
  }
  friend const Number
    operator-(const Number&, const Number&);
};

const Number
  operator-(const Number& n1,
            const Number& n2) {
    return Number(n1.i - n2.i);
}

int main() {
  Number a(47), b(11);
  a + b; // Correcto
  a + 1; // 2º arg. convertido a Number
//! 1 + a; // ¡Mal! El 1er arg. no es de tipo Number
  a - b; // Correcto
  a - 1; // 2º arg. convertido a Number
  1 - a; // 1er arg. convertido a Number
} ///:~
