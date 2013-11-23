#include "articulo.h"
#include <iostream>
#include <iomanip>
using namespace std;

Articulo::Articulo(Cadena ref, Cadena titulo, Fecha fecha, double precio, unsigned cant) : referencia_(ref), titulo_(titulo), salida_(fecha), precio_(precio), stock_(cant){} 

ostream& operator<<(ostream& os, const Articulo& a){
  os << "[" << a.referencia() << "] ";
  os << "\"" << a.titulo() << "\", ";
  os << a.f_publi().anno() << ". ";
  os << fixed;
  os << setprecision(2) << a.precio() << " €";
  
  return os;
}