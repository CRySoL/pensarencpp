//: C16:TStack2.h
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Stack como plantilla con iterador anidado
#ifndef TSTACK2_H
#define TSTACK2_H

template<class T> class Stack {
  struct Link {
    T* data;
    Link* next;
    Link(T* dat, Link* nxt)
      : data(dat), next(nxt) {}
  }* head;
public:
  Stack() : head(0) {}
  ~Stack();
  void push(T* dat) {
    head = new Link(dat, head);
  }
  T* peek() const { 
    return head ? head->data : 0;
  }
  T* pop();
  // Clase iterador anidada:
  class iterator; // Declaración necesaria
  friend class iterator; // Hacerlo amigo
  class iterator { // Ahora se define
    Stack::Link* p;
  public:
    iterator(const Stack<T>& tl) : p(tl.head) {}
    // Constructor de copia:
    iterator(const iterator& tl) : p(tl.p) {}
    // El iterador centinela final:
    iterator() : p(0) {}
    // operator++ devuelve un bool que indica el final:
    bool operator++() {
      if(p->next)
        p = p->next;
      else p = 0; // Indica el final de la lista
      return bool(p);
    }
    bool operator++(int) { return operator++(); }
    T* current() const {
      if(!p) return 0;
      return p->data;
    }
    // Operador de dereferencia de puntero:
    T* operator->() const { 
      require(p != 0, 
        "PStack::iterator::operator->returns 0");
      return current(); 
    }
    T* operator*() const { return current(); }
    // Conversión a bool para pruebas condicionales:
    operator bool() const { return bool(p); }
    // Comparación para detectar el final:
    bool operator==(const iterator&) const {
      return p == 0;
    }
    bool operator!=(const iterator&) const {
      return p != 0;
    }
  };
  iterator begin() const { 
    return iterator(*this); 
  }
  iterator end() const { return iterator(); }
};

template<class T> Stack<T>::~Stack() {
  while(head)
    delete pop();
}

template<class T> T* Stack<T>::pop() {
  if(head == 0) return 0;
  T* result = head->data;
  Link* oldHead = head;
  head = head->next;
  delete oldHead;
  return result;
}
#endif // TSTACK2_H ///:~
