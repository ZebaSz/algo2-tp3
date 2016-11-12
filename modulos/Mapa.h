#ifndef ALGO2_TP3_MAPA_H
#define ALGO2_TP3_MAPA_H

#include "../aed2/Conj.h"
#include "../aed2/Vector.h"
#include "../TiposJuego.h"
#include "../debug.h"

class Mapa {
private:
    struct dataPos;
public:
    Mapa();

    Mapa(const Mapa&);

    void AgregarCoor(const Coordenada&);

    aed2::Conj<Coordenada> Coordenadas() const;

    bool PosExistente(const Coordenada &) const;

    bool HayCamino(const Coordenada&, const Coordenada&) const;

    aed2::Nat Alto();

    aed2::Nat Ancho();

    friend bool operator==(const Mapa&, const Mapa&);

    friend bool operator!=(const Mapa&, const Mapa&);

#ifdef DEBUG
    friend const aed2::Vector< aed2::Vector< dataPos > >& Posiciones(const Mapa&);
#endif

private:
    struct dataPos {
        dataPos() : existe(false) {}

        bool existe;

        aed2::Nat grupo;
    };

    aed2::Vector< aed2::Vector< dataPos > > _posiciones;

    aed2::Nat _alto;

    aed2::Nat _ancho;

    aed2::Nat _proxGrupo;

    void Unir(const Coordenada&, const Coordenada&);
};


#endif //ALGO2_TP3_MAPA_H
