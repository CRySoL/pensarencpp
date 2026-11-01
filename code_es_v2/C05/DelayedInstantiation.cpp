//: C05:DelayedInstantiation.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Los métodos de las plantillas de clase no se
// instancian hasta que hacen falta.

class X {
public:
  void f() {}
};

class Y {
public:
  void g() {}
};

template<typename T> class Z {
  T t;
public:
  void a() { t.f(); }
  void b() { t.g(); }
};

int main() {
  Z<X> zx;
  zx.a(); // No crea Z<X>::b()
  Z<Y> zy;
  zy.b(); // No crea Z<Y>::a()
} ///:~
