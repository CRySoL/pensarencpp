//: C04:Cppcheck.cpp
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Prepara los ficheros .h y .cpp según la norma de estilo.
// Comprueba si los ficheros existentes la cumplen.
#include <fstream>
#include <sstream>
#include <string>
#include <cstddef>
#include "../require.h"
using namespace std;

bool startsWith(const string& base, const string& key) {
  return base.compare(0, key.size(), key) == 0;
}

void cppCheck(string fileName) {
  enum bufs { BASE, HEADER, IMPLEMENT, HLINE1, GUARD1,
    GUARD2, GUARD3, CPPLINE1, INCLUDE, BUFNUM };
  string part[BUFNUM];
  part[BASE] = fileName;
  // Busca un '.' en la cadena:
  size_t loc = part[BASE].find('.');
  if(loc != string::npos)
    part[BASE].erase(loc); // Quita la extensión
  // Pasa a mayúsculas:
  for(size_t i = 0; i < part[BASE].size(); i++)
    part[BASE][i] = toupper(part[BASE][i]);
  // Crea los nombres de fichero y las líneas internas:
  part[HEADER] = part[BASE] + ".h";
  part[IMPLEMENT] = part[BASE] + ".cpp";
  part[HLINE1] = "//" ": " + part[HEADER];
  part[GUARD1] = "#ifndef " + part[BASE] + "_H";
  part[GUARD2] = "#define " + part[BASE] + "_H";
  part[GUARD3] = "#endif // " + part[BASE] +"_H";
  part[CPPLINE1] = string("//") + ": " + part[IMPLEMENT];
  part[INCLUDE] = "#include \"" + part[HEADER] + "\"";
  // Primero intenta abrir los ficheros existentes:
  ifstream existh(part[HEADER].c_str()),
           existcpp(part[IMPLEMENT].c_str());
  if(!existh) { // No existe; se crea
    ofstream newheader(part[HEADER].c_str());
    assure(newheader, part[HEADER].c_str());
    newheader << part[HLINE1] << endl
              << part[GUARD1] << endl
              << part[GUARD2] << endl << endl
              << part[GUARD3] << endl;
  } else { // Ya existe; se comprueba
    stringstream hfile; // Escritura y lectura
    ostringstream newheader; // Escritura
    hfile << existh.rdbuf();
    // Comprueba que las tres primeras líneas cumplen la norma:
    bool changed = false;
    string s;
    hfile.seekg(0);
    getline(hfile, s);
    bool lineUsed = false;
    // La llamada a good() es para Microsoft (más abajo también):
    for(int line = HLINE1; hfile.good() && line <= GUARD2;
         ++line) {
      if(startsWith(s, part[line])) {
        newheader << s << endl;
        lineUsed = true;
        if(getline(hfile, s))
          lineUsed = false;
      } else {
        newheader << part[line] << endl;
        changed = true;
        lineUsed = false;
      }
    }
    // Copia el resto del fichero
    if(!lineUsed)
      newheader << s << endl;
    newheader << hfile.rdbuf();
    // Comprueba si está GUARD3
    string head = hfile.str();
    if(head.find(part[GUARD3]) == string::npos) {
      newheader << part[GUARD3] << endl;
      changed = true;
    }
    // Si ha habido cambios, sobrescribe el fichero:
    if(changed) {
      existh.close();
      ofstream newH(part[HEADER].c_str());
      assure(newH, part[HEADER].c_str());
      newH << "//@//\n"  // Marca de cambio
           << newheader.str();
    }
  }
  if(!existcpp) { // Crea el fichero cpp
    ofstream newcpp(part[IMPLEMENT].c_str());
    assure(newcpp, part[IMPLEMENT].c_str());
    newcpp << part[CPPLINE1] << endl
           << part[INCLUDE] << endl;
  } else { // Ya existe; se comprueba
    stringstream cppfile;
    ostringstream newcpp;
    cppfile << existcpp.rdbuf();
    // Comprueba que las dos primeras líneas cumplen la norma:
    bool changed = false;
    string s;
    cppfile.seekg(0);
    getline(cppfile, s);
    bool lineUsed = false;
    for(int line = CPPLINE1;
        cppfile.good() && line <= INCLUDE; ++line) {
      if(startsWith(s, part[line])) {
        newcpp << s << endl;
        lineUsed = true;
        if(getline(cppfile, s))
          lineUsed = false;
      } else {
        newcpp << part[line] << endl;
        changed = true;
        lineUsed = false;
      }
    }
    // Copia el resto del fichero
    if(!lineUsed)
      newcpp << s << endl;
    newcpp << cppfile.rdbuf();
    // Si ha habido cambios, sobrescribe el fichero:
    if(changed) {
      existcpp.close();
      ofstream newCPP(part[IMPLEMENT].c_str());
      assure(newCPP, part[IMPLEMENT].c_str());
      newCPP << "//@//\n"  // Marca de cambio
             << newcpp.str();
    }
  }
}

int main(int argc, char* argv[]) {
  if(argc > 1)
    cppCheck(argv[1]);
  else
    cppCheck("cppCheckTest.h");
} ///:~
