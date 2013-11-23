#include "tarjeta.h"
#include <ctype.h>
#include <cstring>
#include <iostream>
#include <iomanip>


using namespace std;

bool luhn(const Cadena& numero, size_t n);

Numero::Numero(const Cadena& num){
  char * aux = new char[num.length() + 1];
  unsigned j = 0;
  
  for(unsigned i = 0; i < num.length(); ++i){
    if(isdigit(num[i])) //es un numero
      aux[j++] = num[i];
    else if (!isspace(num[i])) //no es un espacio
      throw Numero::Incorrecto(DIGITOS);
  }
  
  aux[j] = '\0';
  
  if(j > 19 || j < 13) throw Numero::Incorrecto(LONGITUD);
  
  if(!luhn(aux,j)) throw Numero::Incorrecto(NO_VALIDO);
  
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