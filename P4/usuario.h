#ifndef USUARIO_H
#define USUARIO_H

#include <unistd.h>
#include <iostream>
#include "cadena.h"
#include "articulo.h"
#include <map>
#include <set>

using namespace std;

class Tarjeta;
class Numero;

class Clave{
   public:
     enum Razon{CORTA, ERROR_CRYPT};
     class Incorrecta{
        public:
	  Incorrecta(Razon r) : razon_(r){}
	  Razon razon()const{return razon_;}
        private:
	  Razon razon_;
    };
    
    Clave(const char* cad);
    
    Cadena clave()const{return cifrado;}
    
    bool verifica(const char* cad)const;
   private:
     Cadena cifrado;
};

//--------------------------------------------------------------------USUARIO-----------------------------------------------------------------

class Usuario{
   public:
      class Id_duplicado{
        public:
	  Id_duplicado(Cadena id) : repetido(id){}
	  inline Cadena idd()const{return repetido;}
        private:
	  Cadena repetido;
      };
     
     typedef map<Numero, Tarjeta*> Tarjetas;
     typedef map<Articulo*, unsigned> Articulos; 
      
     Usuario(Cadena id, Cadena nom, Cadena ape, Cadena dir, Clave pass);
     
     //Observadores
     Cadena id()const{return identificador_;}
     Cadena nombre()const{return nombre_;}
     Cadena apellidos()const{return apellidos_;}
     Cadena direccion()const{return direccion_;}
     const Tarjetas& tarjetas()const{return tarjetas_;}
     const Articulos& compra()const{return carrito_;}
     size_t n_articulos()const{return carrito_.size();}
     
     void compra(Articulo& a, unsigned cant = 1);
     
     friend ostream& operator<<(ostream& os, const Usuario& u);
     
     void es_titular_de(Tarjeta& tar);
     void no_es_titular_de(Tarjeta& tar);
     
     ~Usuario();
     
   private:
     Cadena identificador_, nombre_, apellidos_, direccion_;
     Clave clave_;
     Tarjetas tarjetas_;
     Articulos carrito_;
     
     Usuario(const Usuario&); //lo declaramos private para que no pueda usarse
     Usuario operator=(const Usuario&);
     
     static set<Cadena> historial;

};

void mostrar_carro(ostream& os, const Usuario& u);

#endif
