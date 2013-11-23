#ifndef _TARJETA_
#define _TARJETA_

#include "fecha.h"
#include "cadena.h"
#include "usuario.h"

using namespace std;

class Usuario;

class Numero{
   public:
     enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
     class Incorrecto{
        public:
	  Incorrecto(Razon r) : razon_(r){}
	  Razon razon()const{return razon_;}
        private:
	  Razon razon_;
    };
     explicit Numero(const Cadena& num);
     operator const char*()const;
     
   private:
     Cadena numero_;
  
};

bool operator<(const Numero& n1, const Numero& n2);

//----------------------------------------------------------------------------TARJETA-----------------------------------------------------------------

class Tarjeta{
   public:
     class Caducada{
        public:
	  Caducada(Fecha caduca) : caduca_(caduca){}
	  inline Fecha cuando()const{return caduca_;}
        private:
	  Fecha caduca_;
     };
     
     Tarjeta(Numero n, Usuario& us, Fecha fecha);
     
     Numero numero()const{return num;}
     Fecha caducidad()const{return caducidad_;}
     Cadena titular_facial()const{return titular_facial_;}
     const Usuario* titular()const{return titular_;}
   
     void anula_titular();
     
     ~Tarjeta();
   private:  
     Numero num;
     const Usuario* titular_;
     Fecha caducidad_;
     Cadena titular_facial_;
     
     Tarjeta(const Tarjeta&);
     Tarjeta operator=(const Tarjeta&);
  
};

ostream& operator<<(ostream& os, const Tarjeta& t);
bool operator<(const Tarjeta& t1, const Tarjeta& t2);

#endif