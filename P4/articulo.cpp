#include "articulo.h"
#include <iostream>
#include <iomanip>
#include <typeinfo>

using namespace std;

Articulo::Articulo(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double precio) : referencia_(ref), titulo_(titulo), salida_(fecha), precio_(precio) {
   if (autores.empty()) throw Autores_vacios();
   
   autores_=autores;
} 

void Libro::imp_esp(ostream& os) const{
   os << n_pag() << " págs., " << stock() << " unidades.";  
}

void Cederron::imp_esp(ostream& os) const{
  os << tam() << " MB, " << stock() << " unidades.";
}

void LibroDigital::imp_esp(ostream& os) const{
  os << "A la venta hasta el " << f_expir() << ".";
}

ostream& operator<<(ostream& os, const Articulo& a){
  os << "[" << a.referencia() << "] ";
  os << "\"" << a.titulo() << "\", " << "de ";
  
  for(Articulo::Autores::const_iterator i = a.autores().begin(); i != a.autores().end(); ++i){
     if(i == a.autores().begin())
       os << (*i)->apellidos();
     else{
       os << ", " << (*i)->apellidos();
     }
  } 
  
  os << ". " << a.f_publi().anno() << ". ";
  os << fixed << setprecision(2) << a.precio() << " €\n\t";
  
  a.imp_esp(os);
  
  return os;
}