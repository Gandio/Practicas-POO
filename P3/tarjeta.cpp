#include "tarjeta.h"
#include "cadena.h"
#include <ctype.h>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm> 
#include <functional>

using namespace std;

bool luhn(const Cadena& numero, size_t n);

Numero::Numero(const Cadena& num){
  unsigned n = num.length();
  char * aux = new char[n + 1];
  strcpy(aux, num.c_str());
  
  char* numbegin = aux;
  char* numend = aux+n;
  
  numend = remove_if(numbegin, numend, EsBlanco()); //remove_if coloca lo que cumpla el predicado al final de la cadena, no los elimina
  *numend = '\0';
  
  n = strlen(aux);

  if(find_if(numbegin, numend, not1(EsDigito())) != numend) throw Numero::Incorrecto(DIGITOS);
  
  
  if(n > 19 || n < 13) throw Numero::Incorrecto(LONGITUD);
  
  if(!luhn(aux,n)) throw Numero::Incorrecto(NO_VALIDO);
  
  numero_ = aux;
  delete[] aux;
}

Numero::operator const char*()const{
  return numero_.c_str();
}

bool operator <(const Numero& n1, const Numero& n2){
  return (strcmp(n1,n2) < 0);
  
}

//-------------------------------------------------------------TARJETA----------------------------------------

Tarjeta::Tarjeta(Numero n, Usuario& us, Fecha fecha) : num(n), titular_(&us){
  titular_facial_ = us.nombre();
  titular_facial_ += " ";
  titular_facial_ += us.apellidos();
  
  Fecha actual;
  if(actual > fecha) throw Tarjeta::Caducada(fecha);
  caducidad_ = fecha;
  
  us.es_titular_de(*this);
}
     
void Tarjeta::anula_titular(){
  titular_ = nullptr;
}
     
Tarjeta::~Tarjeta(){
  Usuario* user = const_cast<Usuario*>(titular_);
  if(user != 0) user->no_es_titular_de(*this);
}

ostream& operator<<(ostream& os, const Tarjeta& t){
  os << t.numero() << endl;
  os << t.titular_facial() << endl;
  os << setfill('0');
  os << "Caduca: " << setw(2) << t.caducidad().mes() << "/" << t.caducidad().anno() % 100 << endl;
  
  return os;
}

bool operator<(const Tarjeta& t1, const Tarjeta& t2){
  return t1.numero() < t2.numero();
}