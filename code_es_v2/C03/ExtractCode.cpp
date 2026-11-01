//: C03:ExtractCode.cpp {-edg} {RunByHand}
// From "Thinking in C++, Volume 2", by Bruce Eckel & Chuck Allison.
// (c) 1995-2004 MindView, Inc. All Rights Reserved.
// See source code use permissions stated in the file 'License.txt',
// distributed with the code package available at www.MindView.net.
// Extrae el código de un texto.
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Cabecera de C heredada y no estándar para mkdir()
#if defined(__GNUC__) || defined(__MWERKS__)
#include <sys/stat.h>
#elif defined(__BORLANDC__) || defined(_MSC_VER) \
  || defined(__DMC__)
#include <direct.h>
#else
#error Compiler not supported
#endif

// Comprueba si existe el directorio
// intentando abrir en él un fichero nuevo
// para escritura.
bool exists(string fname) {
  size_t len = fname.length();
  if(fname[len-1] != '/' && fname[len-1] != '\\')
    fname.append("/");
  fname.append("000.tmp");
  ofstream outf(fname.c_str());
  bool existFlag = outf;
  if(outf) {
    outf.close();
    remove(fname.c_str());
  }
  return existFlag;
}

int main(int argc, char* argv[]) {
  // Comprueba si se ha indicado el fichero de entrada
  if(argc == 1) {
    cerr << "usage: extractCode file [dir]" << endl;
    exit(EXIT_FAILURE);
  }
  // Comprueba si existe el fichero de entrada
  ifstream inf(argv[1]);
  if(!inf) {
    cerr << "error opening file: " << argv[1] << endl;
    exit(EXIT_FAILURE);
  }
  // Comprueba el directorio de salida opcional
  string root("./");  // por defecto, el actual
  if(argc == 3) {
    // Comprueba si existe el directorio de salida
    root = argv[2];
    if(!exists(root)) {
      cerr << "no such directory: " << root << endl;
      exit(EXIT_FAILURE);
    }
    size_t rootLen = root.length();
    if(root[rootLen-1] != '/' && root[rootLen-1] != '\\')
      root.append("/");
  }
  // Lee el fichero de entrada línea a línea
  // buscando los delimitadores de código
  string line;
  bool inCode = false;
  bool printDelims = true;
  ofstream outf;
  while(getline(inf, line)) {
    size_t findDelim = line.find("//" "/:~");
    if(findDelim != string::npos) {
      // Escribe la última línea y cierra el fichero
      if(!inCode) {
        cerr << "Lines out of order" << endl;
        exit(EXIT_FAILURE);
      }
      assert(outf);
      if(printDelims)
        outf << line << endl;
      outf.close();
      inCode = false;
      printDelims = true;
    } else {
      findDelim = line.find("//" ":");
      if(findDelim == 0) {
        // Comprueba si hay directiva '!'
        if(line[3] == '!') {
          printDelims = false;
          ++findDelim;  // Salta '!' en la siguiente búsqueda
        }
        // Extrae el nombre del subdirectorio, si lo hay
        size_t startOfSubdir =
          line.find_first_not_of(" \t", findDelim+3);
        findDelim = line.find(':', startOfSubdir);
        if(findDelim == string::npos) {
          cerr << "missing filename information\n" << endl;
          exit(EXIT_FAILURE);
        }
        string subdir;
        if(findDelim > startOfSubdir)
          subdir = line.substr(startOfSubdir,
                               findDelim - startOfSubdir);
        // Extrae el nombre del fichero (¡más vale que lo haya!)
        size_t startOfFile = findDelim + 1;
        size_t endOfFile =
          line.find_first_of(" \t", startOfFile);
        if(endOfFile == startOfFile) {
          cerr << "missing filename" << endl;
          exit(EXIT_FAILURE);
        }
        // Ya están todas las piezas; forma la ruta fullPath
        string fullPath(root);
        if(subdir.length() > 0)
          fullPath.append(subdir).append("/");
        assert(fullPath[fullPath.length()-1] == '/');
        if(!exists(fullPath))
#if defined(__GNUC__) || defined(__MWERKS__)
          mkdir(fullPath.c_str(), 0);  // Crea el subdirectorio
#else
          mkdir(fullPath.c_str());  // Crea el subdirectorio
#endif
        fullPath.append(line.substr(startOfFile,
                        endOfFile - startOfFile));
        outf.open(fullPath.c_str());
        if(!outf) {
          cerr << "error opening " << fullPath
               << " for output" << endl;
          exit(EXIT_FAILURE);
        }
        inCode = true;
        cout << "Processing " << fullPath << endl;
        if(printDelims)
          outf << line << endl;
      }
      else if(inCode) {
        assert(outf);
        outf << line << endl;  // Escribe una línea intermedia
      }
    }
  }
  exit(EXIT_SUCCESS);
} ///:~
