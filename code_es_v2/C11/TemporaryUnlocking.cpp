//: C11:TemporaryUnlocking.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Desbloqueo temporal de otra guarda.
//{L} ZThread
#include "zthread/Thread.h"
#include "zthread/Mutex.h"
#include "zthread/Guard.h"
using namespace ZThread;

class TemporaryUnlocking {
  Mutex lock;
public:
  void f() {
    Guard<Mutex> g(lock);
    // se adquiere el bloqueo
    // ...
    {
      Guard<Mutex, UnlockedScope> h(g);
      // se libera el bloqueo
      // ...
      // se adquiere el bloqueo
    }
    // ...
    // se libera el bloqueo
  }
};

int main() {
  TemporaryUnlocking t;
  t.f();
} ///:~
