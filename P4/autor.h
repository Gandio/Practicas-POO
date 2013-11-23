#ifndef AUTOR_H
#define AUTOR_H

#include "cadena.h"

class Autor{
   public:      
      Autor(const Cadena& nom, const Cadena& apell, const Cadena& dir) : nombre_(nom), apellidos_(apell), direccion_(dir){}
      
      Cadena nombre()const{return nombre_;}
      Cadena apellidos()const{return apellidos_;}
      Cadena direccion()const{return direccion_;}
      
   private:
     Cadena nombre_, apellidos_, direccion_;
};

#endif