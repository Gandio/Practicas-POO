#ifndef ARTICULO_H
#define ARTICULO_H

#include "cadena.h"
#include "fecha.h"
#include "autor.h"

#include <set>

using namespace std;

class Articulo{
   public:
     
     class Autores_vacios{
        public:
           Autores_vacios(){}
     };
     
     typedef set <Autor*> Autores;
     Articulo(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double precio);
     
    Cadena referencia()const{return referencia_;}
    Cadena titulo()const{return titulo_;}
    Fecha f_publi()const{return salida_;}
    double precio()const{return precio_;}
    const Autores&  autores()const{return autores_;}
    
    double& precio(){return precio_;}
    
    virtual void imp_esp(ostream& os) const  = 0;
    
    virtual ~Articulo() {}
    
   private:
     Autores autores_;
     Cadena referencia_, titulo_; 
     Fecha salida_;  
     double precio_; 
  
};

ostream& operator<<(ostream& os, const Articulo& a);


class ArticuloAlmacenable : public Articulo{
   public:
      ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double precio, unsigned cant) : 
         Articulo(autores, ref, titulo, fecha, precio), stock_(cant) {}
      
      unsigned stock()const{return stock_;}
      unsigned& stock(){return stock_;}
      
      virtual void imp_esp(ostream& os) const  = 0;
      
      virtual ~ArticuloAlmacenable() {}
      
   private:
     unsigned stock_;
};

class Libro : public ArticuloAlmacenable{
   public:
     Libro(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double precio, unsigned pag, unsigned cant) : 
        ArticuloAlmacenable(autores, ref, titulo, fecha, precio, cant), n_pag_(pag) {}
     
     unsigned n_pag()const{return n_pag_;}
     void imp_esp(ostream& os) const;

   private:
     unsigned n_pag_;  
};

class Cederron : public ArticuloAlmacenable{
   public:
     Cederron(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double precio, unsigned capacidad, unsigned cant) :
        ArticuloAlmacenable(autores, ref, titulo, fecha, precio, cant), tam_(capacidad) {}
     
     unsigned tam()const{return tam_;}
     void imp_esp(ostream& os) const;
     
   private:
      unsigned tam_;  
};

class LibroDigital : public Articulo{
   public:
      LibroDigital(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double precio, const Fecha& f) :
         Articulo(autores, ref, titulo, fecha, precio) , f_expir_(f) {}
         
      Fecha f_expir()const{return f_expir_;}
      void imp_esp(ostream& os) const;
      
   private:
      Fecha f_expir_;     
};

#endif