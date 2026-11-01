//: C08:Constag.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Constantes y agregados
const int i[] = { 1, 2, 3, 4 };
//! float f[i[3]]; // Ilegal
struct S { int i, j; };
const S s[] = { { 1, 2 }, { 3, 4 } };
//! double d[s[1].j]; // Ilegal
int main() {} ///:~
