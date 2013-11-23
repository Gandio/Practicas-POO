#include "fecha.h"
#include <ctime>
#include <cstdio>
#include <iostream>

using namespace std;

bool Fecha::compruebaFecha()const{
  int vec_mes[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  
  if(mes_<1 || mes_>12) return false;
  if(ayo_>Fecha::AnnoMaximo || ayo_<Fecha::AnnoMinimo) return false;
  if(ayo_ % 4 == 0 && (ayo_ % 400 == 0 || ayo_ % 100 != 0 )) vec_mes[1]++;
  if(dia_>vec_mes[mes_-1] || dia_<1) return false;

  return true;
}

Fecha::Fecha(int dia, int mes, int ayo): dia_(dia), mes_(mes), ayo_(ayo){
  std::time_t tiempo_cal = std::time(nullptr);
  std::tm* tiempo_desc = std::localtime(&tiempo_cal);
  
  if(dia==0) dia_ = tiempo_desc->tm_mday;
  if(mes==0) mes_ = tiempo_desc->tm_mon + 1;
  if(ayo==0) ayo_ = tiempo_desc->tm_year + 1900;
  
  if(!compruebaFecha()) throw Fecha::Invalida("La fecha introducida no es válida");
}

Fecha::Fecha(const char* cad){  
  if(3 != sscanf(cad,"%d/%d/%d",&dia_,&mes_,&ayo_)) throw Fecha::Invalida("La fecha introducida no es válida");
  
  std::time_t tiempo_cal = std::time(nullptr);
  std::tm* tiempo_desc = std::localtime(&tiempo_cal);
  
  if(dia_==0) dia_ = tiempo_desc->tm_mday;
  if(mes_==0) mes_ = tiempo_desc->tm_mon + 1;
  if(ayo_==0) ayo_ = tiempo_desc->tm_year + 1900;
  
  if(!compruebaFecha()) throw Fecha::Invalida("La fecha introducida no es válida");
}

const char* Fecha::cadena()const{
  struct tm * tiempo;
  time_t cal;
  
  time(&cal);
  tiempo = localtime(&cal);
  
  tiempo->tm_year = ayo_ - 1900;
  tiempo->tm_mon = mes_ - 1;
  tiempo->tm_mday = dia_;
  
  mktime(tiempo);
  
  const char* diasem[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
  const char* nombremes[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
  static char salida[36];
  
  sprintf(salida,"%s %2d de %s de %.4d",diasem[tiempo->tm_wday],dia_,nombremes[mes_-1],ayo_);
  
  return salida;
}

Fecha& Fecha::operator+=(int dias){
  int vec_mes[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  if(dias>0){
     for(int n=dias; n>0; --n){
       ++dia_;
       if(dia_>vec_mes[mes_-1]){ 
         dia_=1;
         if(mes_==12){
	   mes_=1;
	   ++ayo_;
         }else
	   ++mes_;
       }
     }
  }else{
    for(int n=dias; n<0; ++n){
      --dia_;
      if(dia_<1){
	if(mes_==1){
	  mes_=12;
	  --ayo_;
	  dia_=vec_mes[mes_-1];
	}else{
	  --mes_;
	  dia_=vec_mes[mes_-1];
       }
     }
   }
  }
  
  if(!compruebaFecha()) throw Fecha::Invalida("La fecha introducida no es válida");
  
  return *this;
}

Fecha& Fecha::operator-=(int dias){
  return (*this += -dias);
}

Fecha Fecha::operator+(int dias)const{
  Fecha aux = *this;
  return (aux += dias);
}

Fecha Fecha::operator-(int dias)const{
  Fecha aux = *this;
  return aux += -dias;
}

Fecha& Fecha::operator++(){
  *this += 1;
  return *this;
  
}

Fecha& Fecha::operator--(){
  *this += -1;
  return *this;
}

Fecha Fecha::operator++(int x){
  Fecha aux = *this;
  *this += 1;
  return aux;
}

Fecha Fecha::operator--(int x){
  Fecha aux = *this;
  *this += -1;
  return aux;
}

bool Fecha::operator==(const Fecha& f)const{
  if(dia_==f.dia_ && mes_==f.mes_ && ayo_==f.ayo_) return true;
  else 
    return false;
}

bool Fecha::operator!=(const Fecha& f)const{
  return !(*this == f);
}

bool Fecha::operator<(const Fecha& f)const{
  if(ayo_ < f.ayo_) return true;
  else if(ayo_ == f.ayo_ && mes_ < f.mes_) return true;
  else if(mes_ == f.mes_ && dia_ < f.dia_) return true;
  else
    return false;
}

bool Fecha::operator>(const Fecha& f)const{
  return (f < *this);
}

bool Fecha::operator<=(const Fecha& f)const{
  return !(*this > f);
}

bool Fecha::operator>=(const Fecha& f)const{
  
  return !(*this < f);
}

ostream& operator<<(ostream& os, const Fecha& f){
  os << f.cadena();
  
  return os;
}

istream& operator>>(istream& is, Fecha& f){
  char cad[11]="";
  is.width(11);
  is>>cad;
  
  Fecha faux(cad);
  f=faux;
  
  return is;
}
