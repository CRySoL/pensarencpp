//: C06:Nojump.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// No se pueden saltar los constructores

class X {
public:
  X();
};

X::X() {}

void f(int i) {
  if(i < 10) {
   //! goto jump1; // Error: goto se salta la inicialización
  }
  X x1;  // Aquí se llama al constructor
 jump1:
  switch(i) {
    case 1 :
      X x2;  // Aquí se llama al constructor
      break;
  //! case 2 : // Error: case se salta la inicialización
      X x3;  // Aquí se llama al constructor
      break;
  }
} 

int main() {
  f(9);
  f(11);
}///:~
