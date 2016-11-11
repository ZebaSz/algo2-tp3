#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_

#include "aed2/TiposBasicos.h"

typedef unsigned int Jugador;
typedef std::string Pokemon;
 
struct Coordenada
{
	aed2::Nat latitud;
    aed2::Nat longitud;
	Coordenada(aed2::Nat latitud, aed2::Nat longitud) : latitud(latitud), longitud(longitud)
	{
	}

    friend std::ostream& operator<< (std::ostream& os, const Coordenada& c) {
        os << '(' << c.latitud << c.longitud << ')';
        return os;
    }

    friend bool operator== (const Coordenada& c1, const Coordenada& c2) {
        return c1.latitud == c2.latitud and c1.longitud == c2.longitud;
    }

    friend bool operator!= (const Coordenada& c1, const Coordenada& c2) {
        return not (c1 == c2);
    }
};


#endif