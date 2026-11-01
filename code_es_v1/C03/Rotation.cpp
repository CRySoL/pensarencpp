//: C03:Rotation.cpp {O}
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Rotaciones a la izquierda y a la derecha

unsigned char rol(unsigned char val) {
  int highbit;
  if(val & 0x80) // 0x80 solo tiene activo el bit alto
    highbit = 1;
  else
    highbit = 0;
  // Desplaza a la izquierda (el bit bajo pasa a 0):
  val <<= 1;
  // Rota el bit alto a la posición más baja:
  val |= highbit;
  return val;
}

unsigned char ror(unsigned char val) {
  int lowbit;
  if(val & 1) // Comprueba el bit bajo
    lowbit = 1;
  else
    lowbit = 0;
  val >>= 1; // Desplaza una posición a la derecha
  // Rota el bit bajo a la posición más alta:
  val |= (lowbit << 7);
  return val;
} ///:~
