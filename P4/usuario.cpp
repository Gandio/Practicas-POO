#include "usuario.h"
#include "cadena.h"
#include "tarjeta.h"
#include "articulo.h"
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <iomanip>

using namespace std;

set<Cadena> Usuario::historial;

Clave::Clave(const char* cad){
  if(strlen(cad) < 5) throw Clave::Incorrecta(CORTA);
  
  const char *const vector = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  
  srand(time(0));
  const char salt[]={vector[rand()%63], vector[rand()%63]};
  
  if(crypt(cad,salt) == 0) throw Clave::Incorrecta(ERROR_CRYPT);
  
  cifrado = crypt(cad,salt);
}

bool Clave::verifica(const char* cad)const{
  return(cifrado == crypt(cad,cifrado.c_str()));
}

//---------------------------------------------------------------USUARIO----------------------------------------------------------------

Usuario::Usuario(Cadena id, Cadena nom, Cadena ape, Cadena dir, Clave pass) : identificador_(id), nombre_(nom), apellidos_(ape), direccion_(dir), clave_(pass){
   if(!(historial.insert(identificador_)).second) throw Usuario::Id_duplicado(id);
} 
     
void Usuario::compra(Articulo& a, unsigned cant){
  if(cant == 0){
    carrito_.erase(&a);
  }else{
    carrito_[&a] = cant; 
  }
}
     
void Usuario::es_titular_de(Tarjeta& tar){
  tarjetas_.insert(make_pair(tar.numero(), &tar));
  
}
void Usuario::no_es_titular_de(Tarjeta& tar){
  tar.anula_titular();
  tarjetas_.erase(tar.numero());
}
     
Usuario::~Usuario(){
  for(Tarjetas::iterator i=tarjetas_.begin(); i != tarjetas_.end(); ++i){
    i->second->anula_titular();
  }
  
  historial.erase(identificador_);
  
}

ostream& operator<<(ostream& os, const Usuario& u){
  os << u.id() << " " << "[" << u.clave_.clave()<< "]" << " " << u.nombre() << " " << u.apellidos() << endl;
  os << u.direccion() << endl;
  os << "Tarjetas:" << endl;
  for(Usuario::Tarjetas::const_iterator i = u.tarjetas().begin(); i != u.tarjetas().end(); ++i){
    os << *(i->second) << endl;
  }
  
  return os;
}

void mostrar_carro(ostream& os, const Usuario& u){
  os << "Carrito de compra de " << u.id() << " " << "[Artículos: " << u.n_articulos() << "]" << endl;
  os << " " << "Cant. Artículo" << endl;
  os << "===========================================================" << endl;
  
  for(Usuario::Articulos::const_iterator i = u.compra().begin(); i != u.compra().end(); ++i){
    os << i->second << " [" << i->first->referencia() << "] ";
    os << "\"" << i->first->titulo() << "\"";
    os << ", " << i->first->f_publi().anno() << ". ";
    os << fixed << setprecision(2) << i->first->precio() << " €" << endl;
  }
}