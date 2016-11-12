#include "Mapa.h"


Mapa::Mapa() : _alto(0), _ancho(0), _proxGrupo(0) {
}

Mapa::Mapa(const Mapa& otro) : _posiciones(otro._posiciones), _alto(otro._alto),
                               _ancho(otro._ancho), _proxGrupo(otro._proxGrupo) {
}

void Mapa::AgregarCoor(const Coordenada& coor) {
    while(_posiciones.Longitud() <= coor.latitud) {
        _posiciones.AgregarAtras(aed2::Vector<dataPos>());
    }
    if(_alto <= coor.latitud) {
        _alto = coor.latitud + 1;
    }
    while(_posiciones[coor.latitud].Longitud() <= coor.longitud) {
        _posiciones[coor.latitud].AgregarAtras(dataPos());
    }
    if(_ancho <= coor.longitud) {
        _ancho = coor.longitud + 1;
    }
    _posiciones[coor.latitud][coor.longitud].existe = true;
    _posiciones[coor.latitud][coor.longitud].grupo = _proxGrupo;

    Unir(coor, Coordenada(coor.latitud + 1, coor.longitud));
    if(coor.latitud > 0) {
        Unir(coor, Coordenada(coor.latitud - 1, coor.longitud));
    }
    Unir(coor, Coordenada(coor.latitud, coor.longitud + 1));
    if(coor.longitud > 0) {
        Unir(coor, Coordenada(coor.latitud, coor.longitud - 1));
    }
    if(_posiciones[coor.latitud][coor.longitud].grupo == _proxGrupo) {
        ++_proxGrupo;
    }
}

aed2::Conj<Coordenada> Mapa::Coordenadas() const {
    aed2::Conj<Coordenada> coordenadas;
    for(aed2::Nat i = 0; i < _alto; ++i) {
        for(aed2::Nat j = 0; j < _posiciones[i].Longitud(); ++j) {
            if(_posiciones[i][j].existe) {
                coordenadas.AgregarRapido(Coordenada(i,j));
            }
        }
    }
    return coordenadas;
}

bool Mapa::PosExistente(const Coordenada &coor) const {
    return coor.latitud < _alto && coor.longitud < _posiciones[coor.latitud].Longitud()
            && _posiciones[coor.latitud][coor.longitud].existe;
}

bool Mapa::HayCamino(const Coordenada& c1, const Coordenada& c2) const {
    return _posiciones[c1.latitud][c1.longitud].grupo == _posiciones[c2.latitud][c2.longitud].grupo;
}

aed2::Nat Mapa::Alto() {
    return _alto;
}

aed2::Nat Mapa::Ancho() {
    return _ancho;
}

bool operator==(const Mapa& m1, const Mapa& m2) {
    return m1.Coordenadas() == m2.Coordenadas();
}
bool operator!=(const Mapa& m1, const Mapa& m2) {
    return not (m1 == m2);
}
std::ostream& operator<<(std::ostream& os, const Mapa& m) {
    return os << m.Coordenadas();
}

void Mapa::Unir(const Coordenada& c1, const Coordenada& c2) {
    if(PosExistente(c1) && PosExistente(c2) && !HayCamino(c1,c2)) {
        aed2::Nat grupoViejo = _posiciones[c1.latitud][c1.longitud].grupo;
        aed2::Nat grupoUnido = _posiciones[c2.latitud][c2.longitud].grupo;
        aed2::Conj<Coordenada> coordenadas = Coordenadas();
        aed2::Conj<Coordenada>::const_Iterador it = coordenadas.CrearIt();
        while(it.HaySiguiente()) {
            Coordenada pos = it.Siguiente();
            if(_posiciones[pos.latitud][pos.longitud].grupo == grupoViejo) {
                _posiciones[pos.latitud][pos.longitud].grupo = grupoUnido;
            }
            it.Avanzar();
        }
    }
}
