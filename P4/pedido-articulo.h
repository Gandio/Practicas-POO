#ifndef PEDIDO_ARTICULO_H
#define PEDIDO_ARTICULO_H

#include "articulo.h"
#include "pedido.h"

#include <map>
#include <functional>
#include <iostream>

using namespace std;

struct OrdenaPedidos : public binary_function<Pedido*, Pedido*, bool> {
   bool operator()(const Pedido* p1, const Pedido* p2)const{return p1->numero() < p2->numero();}
};

struct OrdenaArticulos : public binary_function<Articulo*, Articulo*, bool> {
   bool operator()(const Articulo* a1, const Articulo* a2)const{return a1->referencia() < a2->referencia();}
};

//------------------LINEAPEDIDO-------------------------

class LineaPedido{
   public:
      explicit LineaPedido(double precio, unsigned stock=1);
      double precio_venta()const{return precio_venta_;}
      unsigned cantidad()const{return cantidad_;}
   private:
      double precio_venta_;
      unsigned cantidad_;
};

ostream& operator<<(ostream& os, const LineaPedido& lp);

//--------------------PEDIDOARTICULO-----------------------

class Pedido_Articulo{
   public:
      typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
      typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
      typedef map<Pedido*, ItemsPedido, OrdenaPedidos> PedidoArticulo;
      typedef map<Articulo*, Pedidos, OrdenaArticulos> ArticuloPedido; 
      
      void pedir(Pedido& p, Articulo& a, double precio, unsigned cant=1);
      void pedir(Articulo& a, Pedido& p, double precio, unsigned cant=1);
      
      ItemsPedido& detalle(Pedido& p){return pa.find(&p)->second;}
      Pedidos& ventas(Articulo& a){return ap.find(&a)->second;}
      
      void mostrarDetallePedidos(ostream& os);
      void mostrarVentasArticulos(ostream& os);
   private:  
      PedidoArticulo pa;
      ArticuloPedido ap;
};

ostream& operator<<(ostream& os, const Pedido_Articulo::ItemsPedido& ip);
ostream& operator<<(ostream& os, const Pedido_Articulo::Pedidos& p);

#endif