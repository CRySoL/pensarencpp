//: C08:RTTIandMultipleInheritance.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
#include <iostream>
#include <typeinfo>
using namespace std;

class BB {
public:
  virtual void f() {}
  virtual ~BB() {}
};

class B1 : virtual public BB {};
class B2 : virtual public BB {};
class MI : public B1, public B2 {};

int main() {
  BB* bbp = new MI; // Upcast
  // Detección correcta del nombre:
  cout << typeid(*bbp).name() << endl;
  // dynamic_cast funciona correctamente:
  MI* mip = dynamic_cast<MI*>(bbp);
  // No se puede forzar un molde al estilo antiguo:
//! MI* mip2 = (MI*)bbp; // Error de compilación
} ///:~
