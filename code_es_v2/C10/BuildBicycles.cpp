//: C10:BuildBicycles.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
//{L} Bicycle
// El patrón de diseño Constructor.
#include <cstddef>
#include <iostream>
#include <map>
#include <vector>
#include "Bicycle.h"
#include "../purge.h"
using namespace std;

// Construye una bicicleta mediante un Constructor concreto
Bicycle* buildMeABike(
  BicycleTechnician& t, BicycleBuilder* builder) {
  t.setBuilder(builder);
  t.construct();
  Bicycle* b = builder->getProduct();
  cout << "Built a " << builder->getBikeName() << endl;
  return b;
}

int main() {
  // Crear un pedido de bicicletas
  map <string, size_t> order;
  order["mountain"] = 2;
  order["touring"] = 1;
  order["racing"] = 3;

  // Construir las bicicletas
  vector<Bicycle*> bikes;
  BicycleBuilder* m = new MountainBikeBuilder;
  BicycleBuilder* t = new TouringBikeBuilder;
  BicycleBuilder* r = new RacingBikeBuilder;
  BicycleTechnician tech;
  map<string, size_t>::iterator it = order.begin();
  while(it != order.end()) {
    BicycleBuilder* builder;
    if(it->first == "mountain")
      builder = m;
    else if(it->first == "touring")
      builder = t;
    else if(it->first == "racing")
      builder = r;
    for(size_t i = 0; i < it->second; ++i)
      bikes.push_back(buildMeABike(tech, builder));
    ++it;
  }
  delete m;
  delete t;
  delete r;

  // Mostrar el inventario
  for(size_t i = 0; i < bikes.size(); ++i)
    cout << "Bicycle: " << *bikes[i] << endl;
  purge(bikes);
}

/* Salida:
Built a MountainBike
Built a MountainBike
Built a RacingBike
Built a RacingBike
Built a RacingBike
Built a TouringBike
Bicycle: {
  Frame Wheel Seat Derailleur Handlebar Sprocket Shock }
Bicycle: {
  Frame Wheel Seat Derailleur Handlebar Sprocket Shock }
Bicycle: { Frame Wheel Seat Handlebar Sprocket }
Bicycle: { Frame Wheel Seat Handlebar Sprocket }
Bicycle: { Frame Wheel Seat Handlebar Sprocket }
Bicycle: {
  Frame Wheel Seat Derailleur Handlebar Sprocket Rack }
*/ ///:~
