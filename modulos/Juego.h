#ifndef ALGO2_TP3_JUEGO_H
#define ALGO2_TP3_JUEGO_H

#include "Mapa.h"

class Juego {
public:
    Juego(const Mapa&);

    const Mapa& ObtenerMapa() const;

private:

    const Mapa _mapa;
};


#endif //ALGO2_TP3_JUEGO_H
