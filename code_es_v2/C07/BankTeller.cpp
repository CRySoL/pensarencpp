//: C07:BankTeller.cpp {RunByHand}
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Uso de una cola y de una simulación de varios hilos
// para modelar un sistema de cajeros de banco.
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
using namespace std;

class Customer {
  int serviceTime;
public:
  Customer() : serviceTime(0) {}
  Customer(int tm) : serviceTime(tm) {}
  int getTime() { return serviceTime; }
  void setTime(int newtime) { serviceTime = newtime; }
  friend ostream&
  operator<<(ostream& os, const Customer& c) {
    return os << '[' << c.serviceTime << ']';
  }
};

class Teller {
  queue<Customer>& customers;
  Customer current;
  enum { SLICE = 5 };
  int ttime; // Tiempo que queda de la fracción
  bool busy; // ¿Está atendiendo a un cliente?
public:
  Teller(queue<Customer>& cq)
  : customers(cq), ttime(0), busy(false) {}
  Teller& operator=(const Teller& rv) {
    customers = rv.customers;
    current = rv.current;
    ttime = rv.ttime;
    busy = rv.busy;
    return *this;
  }
  bool isBusy() { return busy; }
  void run(bool recursion = false) {
    if(!recursion)
      ttime = SLICE;
    int servtime = current.getTime();
    if(servtime > ttime) {
      servtime -= ttime;
      current.setTime(servtime);
      busy = true; // Aún atiende al actual
      return;
    }
    if(servtime < ttime) {
      ttime -= servtime;
      if(!customers.empty()) {
        current = customers.front();
        customers.pop(); // Lo saca
        busy = true;
        run(true); // Llamada recursiva
      }
      return;
    }
    if(servtime == ttime) {
      // Terminado el actual, lo deja vacío:
      current = Customer(0);
      busy = false;
      return; // No queda tiempo en esta fracción
    }
  }
};

// Hereda para acceder a la implementación protegida:
class CustomerQ : public queue<Customer> {
public:
  friend ostream&
  operator<<(ostream& os, const CustomerQ& cd) {
    copy(cd.c.begin(), cd.c.end(),
      ostream_iterator<Customer>(os, ""));
    return os;
  }
};

int main() {
  CustomerQ customers;
  list<Teller> tellers;
  typedef list<Teller>::iterator TellIt;
  tellers.push_back(Teller(customers));
  srand(time(0)); // Inicializa la semilla del generador aleatorio
  clock_t ticks = clock();
  // Ejecuta la simulación durante al menos 5 segundos:
  while(clock() < ticks + 5 * CLOCKS_PER_SEC) {
    // Añade a la cola un número aleatorio de clientes,
    // con tiempos de servicio aleatorios:
    for(int i = 0; i < rand() % 5; i++)
      customers.push(Customer(rand() % 15 + 1));
    cout << '{' << tellers.size() << '}'
         << customers << endl;
    // Los cajeros atienden la cola:
    for(TellIt i = tellers.begin();
      i != tellers.end(); i++)
      (*i).run();
    cout << '{' << tellers.size() << '}'
         << customers << endl;
    // Si la cola es demasiado larga, añade otro cajero:
    if(customers.size() / tellers.size() > 2)
      tellers.push_back(Teller(customers));
    // Si la cola es bastante corta, quita un cajero:
    if(tellers.size() > 1 &&
      customers.size() / tellers.size() < 2)
      for(TellIt i = tellers.begin();
        i != tellers.end(); i++)
        if(!(*i).isBusy()) {
          tellers.erase(i);
          break; // Sale del bucle for
        }
  }
} ///:~
