#ifndef _PEDIDO_
#define _PEDIDO_

#include "fecha.h"
#include "tarjeta.h"
#include "usuario.h"
#include "articulo.h"
#include <iostream>
#include <map>

using namespace std;

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
   public:
     class Vacio{
        public:
	   Vacio(Usuario* usu): u(usu){}
	   Usuario& usuario()const{return *u;}
        private:
	   Usuario* u;  
     };
     
     class Impostor{
        public:
	   Impostor(Usuario* usu): u(usu){}
	   Usuario& usuario()const{return *u;}
        private:
	   Usuario* u;
     };
     
     class SinStock{
        public:
	   SinStock(Articulo* ar): a(ar){}
	   Articulo& articulo()const{return *a;} 
        private:
	   Articulo* a;
     };
     
     Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f=Fecha());
     int numero()const{return num_;}
     const Tarjeta* tarjeta()const{return tarjeta_;}
     Fecha fecha()const{return fecha_;}
     double total()const{return total_;}
     static int n_total_pedidos(){return N_pedidos;}
     
   private:
      static int N_pedidos; 
      int num_;
      const Tarjeta* tarjeta_;
      Fecha fecha_;
      double total_;
};

ostream& operator<<(ostream& os, const Pedido& p);

#endif
