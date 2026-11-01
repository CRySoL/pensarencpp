//: C05:TemplateFunctionAddress.cpp {-mwcc}
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Cómo obtener la dirección de una función generada
// a partir de una plantilla.

template<typename T> void f(T*) {}

void h(void (*pf)(int*)) {}

template<typename T> void g(void (*pf)(T*)) {}

int main() {
  h(&f<int>); // Especificación completa del tipo
  h(&f); // Deducción de tipos
  g<int>(&f<int>); // Especificación completa del tipo
  g(&f<int>); // Deducción de tipos
  g<int>(&f); // Especificación parcial (pero suficiente)
} ///:~
