//: C12:Byte.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Operadores sobrecargados como métodos
#ifndef BYTE_H
#define BYTE_H
#include "../require.h"
#include <iostream>
// Métodos (con "this" implícito):
class Byte { 
  unsigned char b;
public:
  Byte(unsigned char bb = 0) : b(bb) {}
  // Sin efectos laterales: método const:
  const Byte
    operator+(const Byte& right) const {
    return Byte(b + right.b);
  }
  const Byte
    operator-(const Byte& right) const {
    return Byte(b - right.b);
  }
  const Byte
    operator*(const Byte& right) const {
    return Byte(b * right.b);
  }
  const Byte
    operator/(const Byte& right) const {
    require(right.b != 0, "divide by zero");
    return Byte(b / right.b);
  }
  const Byte
    operator%(const Byte& right) const {
    require(right.b != 0, "modulo by zero");
    return Byte(b % right.b);
  }
  const Byte
    operator^(const Byte& right) const {
    return Byte(b ^ right.b);
  }
  const Byte
    operator&(const Byte& right) const {
    return Byte(b & right.b);
  }
  const Byte
    operator|(const Byte& right) const {
    return Byte(b | right.b);
  }
  const Byte
    operator<<(const Byte& right) const {
    return Byte(b << right.b);
  }
  const Byte
    operator>>(const Byte& right) const {
    return Byte(b >> right.b);
  }
  // La asignación modifica y devuelve un valor izquierdo.
  // operator= solo puede ser un método:
  Byte& operator=(const Byte& right) {
    // Trata la autoasignación:
    if(this == &right) return *this;
    b = right.b;
    return *this;
  }
  Byte& operator+=(const Byte& right) {
    if(this == &right) {/* autoasignación */}
    b += right.b;
    return *this;
  }
  Byte& operator-=(const Byte& right) {
    if(this == &right) {/* autoasignación */}
    b -= right.b;
    return *this;
  }
  Byte& operator*=(const Byte& right) {
    if(this == &right) {/* autoasignación */}
    b *= right.b;
    return *this;
  }
  Byte& operator/=(const Byte& right) {
    require(right.b != 0, "divide by zero");
    if(this == &right) {/* autoasignación */}
    b /= right.b;
    return *this;
  }
  Byte& operator%=(const Byte& right) {
    require(right.b != 0, "modulo by zero");
    if(this == &right) {/* autoasignación */}
    b %= right.b;
    return *this;
  }
  Byte& operator^=(const Byte& right) {
    if(this == &right) {/* autoasignación */}
    b ^= right.b;
    return *this;
  }
  Byte& operator&=(const Byte& right) {
    if(this == &right) {/* autoasignación */}
    b &= right.b;
    return *this;
  }
  Byte& operator|=(const Byte& right) {
    if(this == &right) {/* autoasignación */}
    b |= right.b;
    return *this;
  }
  Byte& operator>>=(const Byte& right) {
    if(this == &right) {/* autoasignación */}
    b >>= right.b;
    return *this;
  }
  Byte& operator<<=(const Byte& right) {
    if(this == &right) {/* autoasignación */}
    b <<= right.b;
    return *this;
  }
  // Los operadores condicionales devuelven true/false:
  int operator==(const Byte& right) const {
      return b == right.b;
  }
  int operator!=(const Byte& right) const {
      return b != right.b;
  }
  int operator<(const Byte& right) const {
      return b < right.b;
  }
  int operator>(const Byte& right) const {
      return b > right.b;
  }
  int operator<=(const Byte& right) const {
      return b <= right.b;
  }
  int operator>=(const Byte& right) const {
      return b >= right.b;
  }
  int operator&&(const Byte& right) const {
      return b && right.b;
  }
  int operator||(const Byte& right) const {
      return b || right.b;
  }
  // Escribe el contenido en un ostream:
  void print(std::ostream& os) const {
    os << "0x" << std::hex << int(b) << std::dec;
  }
}; 
#endif // BYTE_H ///:~
