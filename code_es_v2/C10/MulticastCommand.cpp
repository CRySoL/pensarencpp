//: C10:MulticastCommand.cpp {RunByHand}
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Desacoplar la gestión de eventos con el patrón Orden.
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// Framework para ejecutar tareas:
class Task {
public:
  virtual void operation() = 0;
};

class TaskRunner {
  static vector<Task*> tasks;
  TaskRunner() {} // Para que sea un Único
  TaskRunner& operator=(TaskRunner&); // No permitido
  TaskRunner(const TaskRunner&); // No permitido
  static TaskRunner tr;
public:
  static void add(Task& t) { tasks.push_back(&t); }
  static void run() {
    vector<Task*>::iterator it = tasks.begin();
    while(it != tasks.end())
      (*it++)->operation();
  }
};

TaskRunner TaskRunner::tr;
vector<Task*> TaskRunner::tasks;

class EventSimulator {
  clock_t creation;
  clock_t delay;
public:
  EventSimulator() : creation(clock()) {
    delay = CLOCKS_PER_SEC/4 * (rand() % 20 + 1);
    cout << "delay = " << delay << endl;
  }
  bool fired() {
    return clock() > creation + delay;
  }
};

// Algo que puede producir eventos asíncronos:
class Button {
  bool pressed;
  string id;
  EventSimulator e; // Para la demostración
public:
  Button(string name) : pressed(false), id(name) {}
  void press() { pressed = true; }
  bool isPressed() {
    if(e.fired()) press(); // Simular el evento
    return pressed;
  }
  friend ostream&
  operator<<(ostream& os, const Button& b) {
    return os << b.id;
  }
};

// El objeto Orden
class CheckButton : public Task {
  Button& button;
  bool handled;
public:
  CheckButton(Button & b) : button(b), handled(false) {}
  void operation() {
    if(button.isPressed() && !handled) {
      cout << button << " pressed" << endl;
      handled = true;
    }
  }
};

// Los procedimientos que hacen el procesamiento principal.
// De vez en cuando hay que "interrumpirlos" para
// comprobar el estado de los botones u otros eventos:
void procedure1() {
  // Aquí van las operaciones de procedure1.
  // ...
  TaskRunner::run(); // Comprobar todos los eventos
}

void procedure2() {
  // Aquí van las operaciones de procedure2.
  // ...
  TaskRunner::run(); // Comprobar todos los eventos
}

void procedure3() {
  // Aquí van las operaciones de procedure3.
  // ...
  TaskRunner::run(); // Comprobar todos los eventos
}

int main() {
  srand(time(0)); // Aleatorizar
  Button b1("Button 1"), b2("Button 2"), b3("Button 3");
  CheckButton cb1(b1), cb2(b2), cb3(b3);
  TaskRunner::add(cb1);
  TaskRunner::add(cb2);
  TaskRunner::add(cb3);
  cout << "Control-C to exit" << endl;
  while(true) {
    procedure1();
    procedure2();
    procedure3();
  }
} ///:~
