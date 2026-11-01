//: C08:PointerAssignment.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
int d = 1;
const int e = 2;
int* u = &d; // Correcto -- d no es const
//! int* v = &e; // Ilegal -- e es const
int* w = (int*)&e; // Legal, pero mala práctica
int main() {} ///:~
