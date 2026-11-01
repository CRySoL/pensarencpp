//: C05:ApplySequence.h
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Aplica una función a un contenedor secuencial de la STL.

// const, 0 argumentos, cualquier tipo de valor de retorno:
template<class Seq, class T, class R>
void apply(Seq& sq, R (T::*f)() const) {
  typename Seq::iterator it = sq.begin();
  while(it != sq.end())
    ((*it++)->*f)();
}

// const, 1 argumento, cualquier tipo de valor de retorno:
template<class Seq, class T, class R, class A>
void apply(Seq& sq, R(T::*f)(A) const, A a) {
  typename Seq::iterator it = sq.begin();
  while(it != sq.end())
    ((*it++)->*f)(a);
}

// const, 2 argumentos, cualquier tipo de valor de retorno:
template<class Seq, class T, class R,
         class A1, class A2>
void apply(Seq& sq, R(T::*f)(A1, A2) const,
    A1 a1, A2 a2) {
  typename Seq::iterator it = sq.begin();
  while(it != sq.end())
    ((*it++)->*f)(a1, a2);
}

// No const, 0 argumentos, cualquier tipo de valor de retorno:
template<class Seq, class T, class R>
void apply(Seq& sq, R (T::*f)()) {
  typename Seq::iterator it = sq.begin();
  while(it != sq.end())
    ((*it++)->*f)();
}

// No const, 1 argumento, cualquier tipo de valor de retorno:
template<class Seq, class T, class R, class A>
void apply(Seq& sq, R(T::*f)(A), A a) {
  typename Seq::iterator it = sq.begin();
  while(it != sq.end())
    ((*it++)->*f)(a);
}

// No const, 2 argumentos, cualquier tipo de valor de retorno:
template<class Seq, class T, class R,
         class A1, class A2>
void apply(Seq& sq, R(T::*f)(A1, A2),
    A1 a1, A2 a2) {
  typename Seq::iterator it = sq.begin();
  while(it != sq.end())
    ((*it++)->*f)(a1, a2);
}
// Etc., hasta el máximo de argumentos que sea probable ///:~
