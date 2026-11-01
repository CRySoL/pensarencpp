//: C07:WildLifeMonitor.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
#include <algorithm>
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class DataPoint {
  int x, y; // Coordenadas de la posición
  time_t time; // Hora del avistamiento
public:
  DataPoint() : x(0), y(0), time(0) {}
  DataPoint(int xx, int yy, time_t tm) :
    x(xx), y(yy), time(tm) {}
  // Valen el operator= y el constructor de copia sintetizados
  int getX() const { return x; }
  int getY() const { return y; }
  const time_t* getTime() const { return &time; }
};

string animal[] = {
  "chipmunk", "beaver", "marmot", "weasel",
  "squirrel", "ptarmigan", "bear", "eagle",
  "hawk", "vole", "deer", "otter", "hummingbird",
};
const int ASZ = sizeof animal/sizeof *animal;
vector<string> animals(animal, animal + ASZ);

// Toda la información está en un "Sighting",
// que se puede enviar a un ostream:
typedef pair<string, DataPoint> Sighting;

ostream&
operator<<(ostream& os, const Sighting& s) {
  return os << s.first << " sighted at x= "
    << s.second.getX() << ", y= " << s.second.getY()
    << ", time = " << ctime(s.second.getTime());
}

// Un generador de objetos Sighting:
class SightingGen {
  vector<string>& animals;
  enum { D = 100 };
public:
  SightingGen(vector<string>& an) : animals(an) {}
  Sighting operator()() {
    Sighting result;
    int select = rand() % animals.size();
    result.first = animals[select];
    result.second = DataPoint(
      rand() % D, rand() % D, time(0));
    return result;
  }
};

// Muestra un menú de animales, deja que el usuario
// elija uno y devuelve su índice:
int menu() {
  cout << "select an animal or 'q' to quit: ";
  for(size_t i = 0; i < animals.size(); i++)
    cout <<'['<< i <<']'<< animals[i] << ' ';
  cout << endl;
  string reply;
  cin >> reply;
  if(reply.at(0) == 'q') return 0;
  istringstream r(reply);
  int i;
  r >> i; // Lo convierte a int
  i %= animals.size();
  return i;
}

int main() {
  typedef multimap<string, DataPoint> DataMap;
  typedef DataMap::iterator DMIter;
  DataMap sightings;
  srand(time(0));  // Inicializa la semilla aleatoria
  generate_n(inserter(sightings, sightings.begin()),
    50, SightingGen(animals));
  // Lo imprime todo:
  copy(sightings.begin(), sightings.end(),
    ostream_iterator<Sighting>(cout, ""));
  // Imprime los avistamientos del animal elegido:
  for(int count = 1; count < 10; count++) {
    // Usa el menú para obtener la selección:
    // int i = menu();
    // Generación aleatoria (para pruebas automáticas):
    int i = rand() % animals.size();
    // Los iteradores de "range" señalan el principio y
    // la posición siguiente al final del rango coincidente:
    pair<DMIter, DMIter> range =
      sightings.equal_range(animals[i]);
    copy(range.first, range.second,
      ostream_iterator<Sighting>(cout, ""));
  }
} ///:~
