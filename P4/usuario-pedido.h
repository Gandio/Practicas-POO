#ifndef USUARIO_PEDIDO_H
#define USUARIO_PEDIDO_H

#include "usuario.h"
#include "pedido.h"
#include <map>
#include <set>

using namespace std;

class Usuario_Pedido{
   public:
      typedef set<Pedido*> Pedidos; 
      typedef map<Usuario*, Pedidos> UsuarioPedidos;
      typedef map<Pedido*, Usuario*> PedidoUsuario;
     
      void asocia(Usuario& u, Pedido& p){up[&u].insert(&p); pu[&p] = &u;}
      void asocia(Pedido& p, Usuario& u){asocia(u,p);}
      
      const Pedidos& pedidos(Usuario& u){return up.find(&u)->second;}
      const Usuario* cliente(Pedido& p){return pu.find(&p)->second;}
   private: 
     UsuarioPedidos up;
     PedidoUsuario pu;
  
};

#endif
