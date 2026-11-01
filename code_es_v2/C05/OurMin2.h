//: C05:OurMin2.h
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Declara min como plantilla exportada
// (Solo funciona con compiladores basados en EDG)
#ifndef OURMIN2_H
#define OURMIN2_H
export template<typename T> const T& min(const T&,
                                         const T&);
#endif // OURMIN2_H ///:~
