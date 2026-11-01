//: C09:Rectangle.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Accesores y mutadores

class Rectangle {
  int wide, high;
public:
  Rectangle(int w = 0, int h = 0)
    : wide(w), high(h) {}
  int width() const { return wide; } // Leer
  void width(int w) { wide = w; } // Modificar
  int height() const { return high; } // Leer
  void height(int h) { high = h; } // Modificar
};

int main() {
  Rectangle r(19, 47);
  // Cambiar la anchura y la altura:
  r.height(2 * r.width());
  r.width(2 * r.height());
} ///:~
