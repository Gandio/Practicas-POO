#include "cadena.h"

#include <stdexcept> 
#include <iostream>
#include <cstring>

using namespace std;

Cadena::Cadena(unsigned lon, char relleno){
  longitud=lon;
  contenido = new char[lon+1];
  
  for(unsigned i=0; i<longitud; i++)
    contenido[i]=relleno;
  
  contenido[longitud]='\0';
}

Cadena::Cadena(const Cadena& cad){
  longitud=strlen(cad.contenido);
  
  contenido=new char[longitud+1];
  strcpy(contenido, cad.contenido);
  
}

Cadena::Cadena(const char* cad){
  longitud=strlen(cad);
  
  contenido=new char[strlen(cad) + 1];
  strcpy(contenido, cad);
  
}

Cadena& Cadena::operator=(const Cadena& c){
  if(this != &c){
     delete[] contenido;
     longitud=c.longitud;
     contenido=new char[longitud+1];
     strcpy(contenido, c.contenido);
  }
  
  return *this;
}

Cadena& Cadena::operator=(const char* cad){
  longitud=strlen(cad);
  delete[] contenido;
  contenido=new char[longitud+1];
  strcpy(contenido, cad);
  
  return *this;
}

const char* Cadena::c_str()const{
  return contenido;
}

bool Cadena::operator==(const Cadena&  c)const{
  if(strcmp(contenido, c.contenido) == 0) return true;
  else return false;
}

bool Cadena::operator!=(const Cadena& c)const{
  return !(*this == c);
}

bool Cadena::operator<=(const Cadena& c)const{
  return !(*this > c);
}

bool Cadena::operator>=(const Cadena& c)const{
  return !(*this < c);
}

bool Cadena::operator<(const Cadena& c)const{
  return !(*this > c) && !(*this == c);
}

bool Cadena::operator>(const Cadena& c)const{
  if(strcmp(contenido, c.contenido) > 0) return true;
  else return false;
}

char& Cadena::operator[](const unsigned& indice){
  return contenido[indice];
}

char Cadena::operator[](const unsigned& indice)const{ //lectura
   return contenido[indice];
  
}

char Cadena::at(const unsigned& indice)const{ //lectura
  if(indice < 0 || indice >= longitud) throw std::out_of_range("Error de rango");
  
  return contenido[indice];
} 

char& Cadena::at(const unsigned& indice){ //escritura
  if(indice < 0 || indice >= longitud) throw std::out_of_range("Error de rango");
  
  return contenido[indice];
}

Cadena Cadena::substr(unsigned indice, unsigned tam)const{
  if(tam >= longitud || indice >= longitud || indice + tam > longitud) throw std::out_of_range("Error de rango");
  
  Cadena caux(tam);
  
  for(unsigned i=0; i <tam; i++){
    caux.contenido[i] = contenido[indice];
    indice++;
  }
  
  return caux;
  
}

Cadena::~Cadena(){
  delete[] contenido;
}

Cadena& Cadena::operator+=(const Cadena& c){
  unsigned lon=length()+c.length()+1;
  char* cad=new char[lon];
  
  strcpy(cad,c_str());
  cad=strcat(cad,c.c_str());
  
  cad[lon] = '\0';
  
  *this=cad;
  
  return *this;
}

//operadores externos a la clase

Cadena operator+(const Cadena& c1, const Cadena& c2){
  Cadena cad(c1);
  cad+=c2;
  
  return cad;
}

ostream& operator<<(ostream& os, const Cadena& cad){
  os << cad.c_str();
  
  return os;
}

istream& operator>>(istream& is, Cadena& cad){
  char caux[32]="";
  is.width(32);
  is>>caux;
  
  cad=caux;
  
  return is;
}