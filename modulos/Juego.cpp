#include "Juego.h"

Juego::Juego(const Mapa& mapa) : _mapa(mapa) {
}

const Mapa &Juego::ObtenerMapa() const {
    return _mapa;
}
