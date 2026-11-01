//: C03:static_cast.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
void func(int) {}

int main() {
  int i = 0x7fff; // Valor positivo máximo = 32767
  long l;
  float f;
  // (1) Conversiones habituales sin molde:
  l = i;
  f = i;
  // También funciona:
  l = static_cast<long>(i);
  f = static_cast<float>(i);

  // (2) Conversiones de estrechamiento:
  i = l; // Puede perder dígitos
  i = f; // Puede perder información
  // Dice "ya lo sé" y elimina los avisos:
  i = static_cast<int>(l);
  i = static_cast<int>(f);
  char c = static_cast<char>(i);

  // (3) Forzar una conversión desde void* :
  void* vp = &i;
  // La forma antigua produce una conversión peligrosa:
  float* fp = (float*)vp;
  // La forma nueva es igual de peligrosa:
  fp = static_cast<float*>(vp);

  // (4) Conversiones de tipo implícitas, que
  // normalmente realiza el compilador:
  double d = 0.0;
  int x = d; // Conversión de tipo automática
  x = static_cast<int>(d); // Más explícito
  func(d); // Conversión de tipo automática
  func(static_cast<int>(d)); // Más explícito
} ///:~
