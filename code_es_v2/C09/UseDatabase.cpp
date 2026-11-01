//: C09:UseDatabase.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
#include "Database.h"

int main() {
  Database db("MyDatabase");
  db.open();
  // Usa otras funciones de db...
  db.close();
}
/* Salida:
connected to MyDatabase
MyDatabase closed
*/ ///:~
