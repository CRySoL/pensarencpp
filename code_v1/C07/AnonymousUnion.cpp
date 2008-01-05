//: C07:AnonymousUnion.cpp
int main() {
  union { 
    int i; 
    float f; 
  };
  // Access members without using qualifiers:
  i = 12;
  f = 1.22;
} ///:~
