//: C11:SynchronizedClass.cpp {-dmc}
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
//{L} ZThread
#include "zthread/GuardedClass.h"
using namespace ZThread;

class MyClass {
public:
  void func1() {}
  void func2() {}
};

int main() {
  MyClass a;
  a.func1(); // No sincronizada
  a.func2(); // No sincronizada
  GuardedClass<MyClass> b(new MyClass);
  // Llamadas sincronizadas (solo se permite un hilo a la vez):
  b->func1();
  b->func2();
} ///:~
