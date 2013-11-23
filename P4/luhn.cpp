// Verifica un número de tarjeta empleando el algoritmo de Luhn
// Referencias: 
//              http://en.wikipedia.org/wiki/Luhn_algorithm
//
#include "cadena.h"		// Cadena
#include <cstddef>		// size_t

// Recibe: una cadena de caracteres numéricos y el n.º de esos caracteres
// Devuelve: verdad si el número es válido, falso si no lo es
bool luhn(const Cadena& numero, size_t n)
{
  size_t suma = 0;
  bool alt = false;
  for (int i = n - 1; i > -1; --i) {
    n = numero[size_t(i)] - '0';
    if (alt) {
      n *= 2;
      if (n > 9)
	n = (n % 10) + 1;
    }
    alt = !alt;
    suma += n;
  }
  return !(suma % 10);
}
