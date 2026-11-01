//: C01:MyError.cpp {RunByHand}
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.

class MyError {
  const char* const data;
public:
  MyError(const char* const msg = 0) : data(msg) {}
};

void f() {
  // Aquí se "lanza" un objeto excepción:
  throw MyError("something bad happened");
}

int main() {
  // Como verá enseguida, aquí conviene un "bloque try":
  f();
} ///:~
