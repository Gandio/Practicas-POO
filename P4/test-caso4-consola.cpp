/* Prueba de la SGL, caso de uso 4
 *
 * LIBRERÍA
 * ©2009-13 Inma, Juanma, Fidel, Gerardo
 */

#include <cstdlib>
#include <exception>
#include <iostream>
#include <locale>
#include "usuario.h"
#include "tarjeta.h"
#include "articulo.h"
#include "autor.h"
#include "pedido.h"
#include "usuario-pedido.h"
#include "pedido-articulo.h"

#define AZUL  "\033[0m\033[01;34m"
#define NORMAL "\033[0m"

using std::cout;
using std::endl;

int main()
{
  cout.imbue(std::locale(""));
    // std::set_terminate(__gnu_cxx::__verbose_terminate_handler);
    // Constructor de usuario: id, nombre, apellidos, dirección, clave
    Usuario 
	lucas("lucas", "Lucas", "Grijánder", 
	      "Avda. Generalísimo, 654 (Barbate)", "vaeg0Quo"),
	krispin("krispin", "Crispín", "Klánder", 
		"C/ del Jurel, 876 (Barbate)", "Pheaj9li"),
	hanna("hannah", "Hannah", "Montana", 
	      "Santa Monica Blvd., Los Ángeles, CA", "ahxo2Aht"),
	rosa("rosa", "Rosita", "de Jericó",
	     "C/ de Sor Sofía, 345 (2 Hermanas)", "Roh9aa5v");
    // Constructor de Tarjeta: Numero, Usuario, fecha de caducidad
    Tarjeta 
	visa1(Numero("4539 4512 0398 7356"), lucas, "31/12/2015"),
	american_express(Numero("378282246310005"), hanna, "30/11/2014"),
	dinners_club(Numero("30569309025904"), rosa, "13/7/2015"),
	mastercard(Numero("555555555555 4444  "), krispin, "1/1/2016"),
	australian_bank_card(Numero("5610591081018250"), krispin, "2/2/2014"),
	jcb(Numero("3530111333300000"), rosa, "7/7/2017"),
	visa2(Numero(" 4222222222222"), lucas, "2/2/2014");
    
    // Constructor de Autor: nombre, apellidos, dirección
    Autor 
	Lucas("Lucas", "Grijánder", "Avda. Generalísimo, 654 (Barbate)"),
	Krispin("Crispín", "Klánder", "C/ del Jurel, 876 (Barbate)"),
    	Hanna("Hannah", "Montana", "Santa Monica Blvd., Los Ángeles, CA"),
	Rosa("Rosita", "de Jericó", "C/ de Sor Sofía, 345 (2 Hermanas)");
    
    Articulo::Autores autores;
    
    // Constructor de Libro: autores, referencia, título, fecha publicación,
    //                       precio, páginas, stock
    autores.insert(&Krispin);
    Libro poo(autores, "100", "Programación Orientada a Objetos",
              "1/8/2000", 32.50, 245, 5); // autor = Krispin

    autores.insert(&Rosa);
    Libro cpp(autores, "110", "Fundamentos de C++",
              "20/6/1998)", 35.95, 650, 100); // autores = Krispin y Rosa
    autores.clear();

    autores.insert(&Lucas);
    Libro stl(autores, "111", "The Standard Template Library",
              "5/10/2002", 42.10, 150, 300); // autor = Lucas
    
    autores.insert(&Hanna);
    Libro ada(autores, "103", "Análisis y Diseño de Algoritmos",
              "1/2/2001", 39.95, 455, 4); // autores = Lucas y Hanna

    // Constructor de LibroDigital: autores, referencia, título,
    //                               fecha publicación, precio, fecha expiración
    LibroDigital  // autores = Lucas y Hanna
        eBook1(autores, "034", "Revisiones", "15/1/2009", 6., "1/7/2009");
    autores.clear();
    
    autores.insert(&Rosa);
    LibroDigital // autor = Rosa
        eBook2(autores, "035", "Horarios", "20/3/2009)", 9., "20/6/2009"),
        eBook3(autores, "036", "Exámenes", "1/10/2007", 12., "30/9/2008"); // expirado

    // Constructor de Cederron: autores, referencia, título, fecha publicación,
    //                          precio, megas, stock
    Cederron // autor = Rosa
        cd1(autores, "210", "El Canto del Loco", "1/8/2000", 32.50, 245, 40);
    
    autores.insert(&Krispin);
    Cederron  // autores = Rosa y Krispin
        cd2(autores, "211", "Mecano", "20/6/1998", 35.95, 650, 50);
    
    autores.insert(&Lucas);
    Cederron  // autores = Rosa, Krispin y Lucas
        cd3(autores, "220", "Música para programar", 
	    "7/7/2007", 12.90, 547, 30);

    cout << "\n" AZUL "---------------INVENTARIO DE EXISTENCIAS-----------"
	NORMAL "\nLIBROS: \n" 
	 << poo << '\n' << cpp << '\n' << stl << '\n' << ada
	 << "\nLIBROS DIGITALES: \n" 
	 << eBook1 << '\n' << eBook2 << '\n' << eBook3
	 << "\nCEDERRONES: \n" 
	 << cd1 << '\n' << cd2 << '\n' << cd3 << endl;

    // Añadir y quitar artículos al carrito y ver el carrito
    // Comprar: Articulo, Cantidad (1 por omisión, 0 elimina el artículo)
    // Factura: Usuario_Pedido, Pedido_Articulo, Usuario, Tarjeta, Fecha [hoy]
    Usuario_Pedido usuario_ped;
    Pedido_Articulo pedido_art;

    cout << "\n\nCARRITOS VACÍOS\n\n";
    mostrar_carro(cout, lucas);
    mostrar_carro(cout, krispin);
    mostrar_carro(cout, hanna);
    mostrar_carro(cout, rosa);
    cout << endl;

    lucas.compra(cpp, 3);
    lucas.compra(stl, 1);
    lucas.compra(eBook1, 2);
    lucas.compra(cd2, 1);
    mostrar_carro(cout, lucas);
    Pedido p1(usuario_ped, pedido_art, lucas, visa1, Fecha(10, 3));

    cout << "*** Cambio de precio de CPP, STL, EBOOK1 y CD1\n\n";
    cpp.precio() = 29.95;	// cambiar precios
    stl.precio() = 44.50; 
    eBook1.precio() = 5.50;
    cd1.precio() = 24.05;
    
    krispin.compra(cpp, 2);
    krispin.compra(stl, 2);
    mostrar_carro(cout, krispin);
    cout << "\n*** krispin devuelve STL y compra POO y CD3\n";
    krispin.compra(stl, 0); // quita stl del carrito
    krispin.compra(poo);    // un ejemplar
    krispin.compra(cd3);
    mostrar_carro(cout, krispin);
    cout << "\n*** No se comprueban existencias\n"
	"*** existencias de ADA = " << ada.stock() << endl;
    hanna.compra(ada, 6);	// no se comprueban las existencias
    cout << "\n*** No se comprueba la fecha de expiración\n"
	"*** fecha expir. eBook3 = " << eBook3.f_expir() << "\n\n";
    hanna.compra(eBook3, 2); // no se comprueba la fecha de expiración
    mostrar_carro(cout, hanna);
    cout << "\n*** hanna devuelve 4 ADA\n";
    hanna.compra(ada, 2);	// quita 4 del carrito
    mostrar_carro(cout, hanna);
    Pedido p3(usuario_ped, pedido_art, hanna, american_express, 
	      --Fecha());	// pedido ayer
    Pedido p2(usuario_ped, pedido_art, krispin, mastercard, "5/4/2010");

    cout << "*** Cambio de precio de POO, ADA y eBook2\n\n";
    poo.precio() = 35.20;	// cambiar precios
    ada.precio() = 34.90; 
    eBook2.precio() = 3.;

    rosa.compra(cd3, 2);
    rosa.compra(eBook2, 3);
    rosa.compra(stl);
    rosa.compra(cd2, 0); // no hace nada, cd2 no está en el carro
    mostrar_carro(cout, rosa);
    Pedido p4(usuario_ped, pedido_art, rosa, jcb, "5/4/2010");

    cout << "\n" AZUL "---------------------PEDIDOS-----------------------"
	NORMAL "\n" << p1 << endl << p2 << endl << p3 << endl << p4 << endl;

    // Recepción de mercancías
    poo.stock() += 5; cpp.stock() *= 4; stl.stock() += 2; ada.stock() += 2;
    
    rosa.compra(stl); rosa.compra(ada);
    Pedido p5(usuario_ped, pedido_art, rosa, jcb); // pedido hoy
    rosa.compra(cpp, 3);
    Pedido p6(usuario_ped, pedido_art, rosa, dinners_club); // pedido hoy
    krispin.compra(ada); krispin.compra(stl); krispin.compra(poo, 3);
    Pedido p7(usuario_ped, pedido_art, krispin, 
	      australian_bank_card, "5/4/2010");
    hanna.compra(poo, 2); hanna.compra(cpp);
    Pedido p8(usuario_ped, pedido_art, hanna, american_express, "5/4/2010");

    cout << p5 << endl << p6 << endl << p7 << endl << p8 << endl

	 << "\n" AZUL "-------------------DETALLE DE PEDIDOS--------------"
	NORMAL "\n";
    pedido_art.mostrarDetallePedidos(cout);
    cout << "\n" AZUL "------------------VENTAS DE ARTÍCULOS--------------"
	NORMAL "\n";
    pedido_art.mostrarVentasArticulos(cout);
    
    cout << "\n" AZUL "-----------------PRUEBAS DE EXCEPCIONES------------"
	NORMAL "\n";
    try {
	   Pedido nulo(usuario_ped, pedido_art, lucas, visa2);
    }
    catch(Pedido::Vacio& e) {
	   std::cerr << "Error de pedido: el carrito de " << e.usuario().id() 
	             << " está vacío. " << endl;
    }
    try {
       krispin.compra(cpp);
       Pedido farsante(usuario_ped, pedido_art, krispin, visa2);
    }
    catch(Pedido::Impostor& e) {
       std::cerr << "Error de pedido: la tarjeta de pago no es de " 
		 << e.usuario().id() << endl;
    }
    try {
       rosa.compra(poo, 2); rosa.compra(stl, 4); rosa.compra(ada, 5);
       Pedido no_disponible(usuario_ped, pedido_art, rosa, dinners_club);
    }
    catch(Pedido::SinStock& e) {
       std::cerr << "Error de pedido: no hay existencias del artículo [" 
                 << e.articulo().referencia() << "]" << endl;
    }
    try {
	// Creamos una tarjeta que caducó ayer. ¿Qué pasa? ¡No somos un
	// maldito banco, esto es una prueba!
	Tarjeta caduca(Numero("4222222222222"), lucas, Fecha() - 1); 
	lucas.compra(poo, 2);
	Pedido no_pagado(usuario_ped, pedido_art, lucas, caduca); // pedido hoy
    }
    catch(Tarjeta::Caducada& e) {
	   std::cerr << "Error de pedido: tarjeta caducada el " << e.cuando()
	             << endl;
    }
    try {
        Articulo::Autores a;
        Libro anonimo(a, "133", "El Necronomicón", 
		      "10/3/2009", 35.00, 210, 4);
    }
    catch(Articulo::Autores_vacios) {
        std::cerr << "Error de artículo: No se puede crear uno anónimo.\n";
    }
    cout << "\nNúmero total de pedidos: " 
	 << Pedido::n_total_pedidos() << '\n' << endl;
}

