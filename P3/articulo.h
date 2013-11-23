#ifndef _ARTICULO_
#define _ARTICULO_

#include "cadena.h"
#include "fecha.h"
using namespace std;

class Articulo{
   public:
     Articulo(Cadena ref, Cadena titulo, Fecha fecha, double precio, unsigned cant);
     
    Cadena referencia()const{return referencia_;}
    Cadena titulo()const{return titulo_;}
    Fecha f_publi()const{return salida_;}
    double precio()const{return precio_;}
    unsigned stock()const{return stock_;}
     
    double& precio(){return precio_;}
    unsigned& stock(){return stock_;}
   private:
     Cadena referencia_, titulo_; 
     Fecha salida_;  
     double precio_; 
     unsigned stock_;
  
};

ostream& operator<<(ostream& os, const Articulo& a);

#endif