#ifndef _FECHA_
#define _FECHA_

#include <iostream>

using namespace std;

class Fecha{
  public:
   class Invalida{
    public:
      Invalida(const char* err): error_(err) {}
      inline const char* por_que() const{return error_;}
    private:
      const char* error_;
  };
   //Constantes
   static const int AnnoMinimo=1903;
   static const int AnnoMaximo=2037;
  
   //Constructores
   explicit Fecha(int dia=0, int mes=0, int ayo=0);
   Fecha(const char* cad);
   
   //Operador de conversion a cadena de caracteres
   const char* cadena()const;
   
   //Operadores artimeticos
   Fecha& operator+=(int dias);
   Fecha& operator-=(int dias);
   Fecha operator+(int dias)const;
   Fecha operator-(int dias)const;
   Fecha& operator++();
   Fecha operator++(int); //post fijo, el parametro int no se usa, solo sirve para distinguirlo respecto al prefijo
   Fecha& operator--();
   Fecha operator--(int);
 
   //Operadores logicos
   bool operator==(const Fecha& f)const;
   bool operator!=(const Fecha& f)const;
   bool operator<(const Fecha& f)const;
   bool operator>(const Fecha& f)const;
   bool operator<=(const Fecha& f)const;
   bool operator>=(const Fecha& f)const;
   
   //Metodos observadores
   inline int dia()const {return dia_;}
   inline int mes()const {return mes_;}
   inline int anno()const {return ayo_;}
 private:
   int dia_, mes_, ayo_;
   bool compruebaFecha()const;
};

//Entrada y salida
ostream& operator<<(ostream& os, const Fecha& f);//insercion
istream& operator>>(istream& is, Fecha& f);//extraccion

#endif