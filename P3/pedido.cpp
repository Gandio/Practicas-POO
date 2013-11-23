#include <ostream>
#include "usuario-pedido.h"
#include "pedido-articulo.h"
#include <iomanip>
#include "fecha.h"
#include "usuario.h"
#include "tarjeta.h"
#include "articulo.h"
#include "pedido.h"
#include <cstring>

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f){
   if(u.compra().begin() == u.compra().end()) throw Pedido::Vacio(&u);
   
   if(t.titular()->nombre() != u.nombre()) throw Pedido::Impostor(&u);
   tarjeta_ = &t;
   
   if(t.caducidad() < f) throw Tarjeta::Caducada(f);
   fecha_ = f;
   
   
   for(Usuario::Articulos::const_iterator it = u.compra().begin(); it != u.compra().end(); ++it){
      if(it->second > it->first->stock()){
	 Articulo *a = it->first;
	 Usuario::Articulos::const_iterator i;
	 for(i = u.compra().begin(); i != u.compra().end(); ++i){
	    u.compra(*(i->first),0);  
	}
	throw Pedido::SinStock(a);
      }    
  }
  
  N_pedidos++;
  num_ = N_pedidos;
  
  up.asocia(*this,u);
  total_ = 0;
  
  for(Usuario::Articulos::const_iterator it = u.compra().begin(); it != u.compra().end(); ++it){
    total_ += it->first->precio() * it->second;
    pa.pedir(*this, *(it->first), it->first->precio(), it->second);
    it->first->stock() = it->first->stock() - it->second;
    u.compra(*(it->first),0);
  }
}

ostream& operator<<(ostream& os, const Pedido& p){
  os << "Núm. pedido: " << p.numero();
  os << endl;
  os << "Fecha: " << p.fecha();
  os << endl;
  os << "Pagado con: " << p.tarjeta()->numero();
  os << endl;
  os << "Importe: ";
  os << fixed;
  os << setprecision(2) << p.total() << " €";
  
  return os;
}