//: C14:SynthesizedFunctions.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Funciones que sintetiza el compilador
#include <iostream>
using namespace std;

class GameBoard {
public:
  GameBoard() { cout << "GameBoard()\n"; }
  GameBoard(const GameBoard&) { 
    cout << "GameBoard(const GameBoard&)\n"; 
  }
  GameBoard& operator=(const GameBoard&) {
    cout << "GameBoard::operator=()\n";
    return *this;
  }
  ~GameBoard() { cout << "~GameBoard()\n"; }
};

class Game {
  GameBoard gb; // Composición
public:
  // Se llama al constructor por defecto de GameBoard:
  Game() { cout << "Game()\n"; }
  // Hay que llamar explícitamente al constructor
  // de copia de GameBoard; si no, se llama
  // automáticamente al constructor por defecto:
  Game(const Game& g) : gb(g.gb) { 
    cout << "Game(const Game&)\n"; 
  }
  Game(int) { cout << "Game(int)\n"; }
  Game& operator=(const Game& g) {
    // Hay que llamar explícitamente al operador
    // de asignación de GameBoard; si no, ¡gb no
    // se asigna en absoluto!
    gb = g.gb;
    cout << "Game::operator=()\n";
    return *this;
  }
  class Other {}; // Clase anidada
  // Conversión automática de tipo:
  operator Other() const {
    cout << "Game::operator Other()\n";
    return Other();
  }
  ~Game() { cout << "~Game()\n"; }
};

class Chess : public Game {};

void f(Game::Other) {}

class Checkers : public Game {
public:
  // Se llama al constructor por defecto de la clase base:
  Checkers() { cout << "Checkers()\n"; }
  // Hay que llamar explícitamente al constructor
  // de copia de la clase base; si no, se llama
  // automáticamente al constructor por defecto:
  Checkers(const Checkers& c) : Game(c) {
    cout << "Checkers(const Checkers& c)\n";
  }
  Checkers& operator=(const Checkers& c) {
    // Hay que llamar explícitamente a la versión
    // de operator=() de la clase base; si no, la
    // parte de la clase base no se asigna:
    Game::operator=(c);
    cout << "Checkers::operator=()\n";
    return *this;
  }
};

int main() {
  Chess d1;  // Constructor por defecto
  Chess d2(d1); // Constructor de copia
//! Chess d3(1); // Error: no hay constructor con int
  d1 = d2; // operator= sintetizado
  f(d1); // La conversión de tipo SÍ se hereda
  Game::Other go;
//!  d1 = go; // operator= no sintetizado
           // para tipos distintos
  Checkers c1, c2(c1);
  c1 = c2;
} ///:~
