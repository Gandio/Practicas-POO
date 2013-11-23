#ifndef _CADENA_
#define _CADENA_

#include <stdexcept> 

class Cadena{
 public:
   
   //Constructores
   explicit Cadena(unsigned lon=0, char relleno = ' ');
   Cadena(const Cadena& cad);
   Cadena(const char* cad);
   
   //operador de conversion
   operator const char*()const;
   
   //observador
   inline unsigned length()const{return longitud;}
   
   //operadores
   Cadena& operator=(const Cadena& c); //operador de asignacion
   Cadena& operator=(const char* cad); //operador de asignacion con conversion
   bool operator==(const Cadena&  c)const;
   bool operator!=(const Cadena& c)const;
   bool operator<=(const Cadena& c)const;
   bool operator>=(const Cadena& c)const;
   bool operator<(const Cadena& c)const;
   bool operator>(const Cadena& c)const;
   char operator[](const unsigned& indice)const; //lectura
   char& operator[](const unsigned& indice); //escritura
   
   //metodos
   char at(const unsigned& indice)const; //lectura
   char& at(const unsigned& indice); //escritura
   Cadena substr(unsigned indice, unsigned tam)const;
   
   //Destructor
   ~Cadena();
   
 private:
   unsigned longitud;
   char* contenido;

};

Cadena& operator+=(Cadena& c1, const Cadena& c2);
Cadena operator+(const Cadena& c1, const Cadena& c2);

#endif