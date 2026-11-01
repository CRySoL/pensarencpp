//: C08:Volatile.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// La palabra reservada volatile

class Comm {
  const volatile unsigned char byte;
  volatile unsigned char flag;
  enum { bufsize = 100 };
  unsigned char buf[bufsize];
  int index;
public:
  Comm();
  void isr() volatile;
  char read(int index) const;
};

Comm::Comm() : index(0), byte(0), flag(0) {}

// Solo es una demostración; no funcionaría
// realmente como rutina de servicio de interrupción:
void Comm::isr() volatile {
  flag = 0;
  buf[index++] = byte;
  // Volver al principio del buffer:
  if(index >= bufsize) index = 0;
}

char Comm::read(int index) const {
  if(index < 0 || index >= bufsize)
    return 0;
  return buf[index];
}

int main() {
  volatile Comm Port;
  Port.isr(); // Correcto
//!  Port.read(0); // Error, read() no es volatile
} ///:~
