//: C08:ConstReturnValues.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Retorno por valor constante
// El resultado no se puede usar como valor izquierdo

class X {
  int i;
public:
  X(int ii = 0);
  void modify();
};

X::X(int ii) { i = ii; }

void X::modify() { i++; }

X f5() {
  return X();
}

const X f6() {
  return X();
}

void f7(X& x) { // Paso por referencia no const
  x.modify();
}

int main() {
  f5() = X(1); // Correcto -- valor de retorno no const
  f5().modify(); // Correcto
//!  f7(f5()); // Provoca un aviso o un error
// Provocan errores de compilación:
//!  f6() = X(1);
//!  f6().modify();
//!  f7(f6());
} ///:~
