//: C03:FileStatic.cpp
// File scope demonstration. Compiling and 
// linking this file with FileStatic2.cpp
// will cause a linker error

// File scope means only available in this file:
static int fs; 

int main() {
  fs = 1;
} ///:~
