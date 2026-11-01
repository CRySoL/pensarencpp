//: C03:SelfReferential.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Cómo permitir que una struct se refiera a sí mismo

typedef struct SelfReferential {
  int i;
  SelfReferential* sr; // ¿Ya le da vueltas la cabeza?
} SelfReferential;

int main() {
  SelfReferential sr1, sr2;
  sr1.sr = &sr2;
  sr2.sr = &sr1;
  sr1.i = 47;
  sr2.i = 1024;
} ///:~
