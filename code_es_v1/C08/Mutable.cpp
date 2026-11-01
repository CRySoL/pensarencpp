//: C08:Mutable.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// La palabra reservada "mutable"

class Z {
  int i;
  mutable int j;
public:
  Z();
  void f() const;
};

Z::Z() : i(0), j(0) {}

void Z::f() const {
//! i++; // Error -- método const
    j++; // Correcto: mutable
}

int main() {
  const Z zz;
  zz.f(); // ¡En realidad lo modifica!
} ///:~
