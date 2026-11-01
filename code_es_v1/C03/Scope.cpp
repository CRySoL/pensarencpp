//: C03:Scope.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Ámbito de las variables
int main() {
  int scp1;
  // scp1 visible aquí
  {
    // scp1 sigue visible aquí
    //.....
    int scp2;
    // scp2 visible aquí
    //.....
    {
      // scp1 y scp2 siguen visibles aquí
      //..
      int scp3;
      // scp1, scp2 y scp3 visibles aquí
      // ...
    } // <-- aquí se destruye scp3
    // scp3 no está disponible aquí
    // scp1 y scp2 siguen visibles aquí
    // ...
  } // <-- aquí se destruye scp2
  // scp3 y scp2 no están disponibles aquí
  // scp1 sigue visible aquí
  //..
} // <-- aquí se destruye scp1
///:~
