#ifndef ALGO2_TP3_JUEGO_H
#define ALGO2_TP3_JUEGO_H

#include "Mapa.h"
#include "../TiposJuego.h"
#include "DiccString.h"
#include "ColaPrior.h"
#include "TuplaOrd.h"

class Juego {
public:
    Juego(const Mapa&);

    void AgregarPokemon(Pokemon pk,Coordenada c);

    aed2::Nat AgregarJugador();

    void Conectarse(Jugador j, Coordenada c);

    void Desconectarse(Jugador j);

    void Moverse(Jugador j, Coordenada c);

    const Mapa& ObtenerMapa() const;

    //TODO: JUGADORES

    bool EstaConectado(Jugador j) const;

    aed2::Nat Sanciones(Jugador j) const;

    Coordenada Posicion(Jugador j) const;

    //TODO: POKEMONS

    //TODO EXPULSADOS

    const aed2::Conj<Coordenada>& PosConPokemons() const;

    const Pokemon& PokemonEnPos(Coordenada c) const;

    bool PuedoAgregarPokemon(Coordenada c) const;

    bool HayPokemonCercano(Coordenada c) const;

    Coordenada PosPokemonCercano(Coordenada c) const;

    aed2::Conj<Jugador> EntrenadoresPosibles(aed2::Conj<Jugador> es, Coordenada c) const;

    aed2::Nat IndiceRareza(Pokemon pk) const;

    aed2::Nat CantPokemonsTotales() const;

    aed2::Nat CantMismaEspecie(Pokemon pk) const;
private:

    struct infoJugador {

        infoJugador() : sanciones(0), conectado(false), posicion(0,0), cantPokemons(0), pokemonsCapturados()  {}

        aed2::Nat sanciones;

        bool conectado;

        Coordenada posicion;

        aed2::Nat cantPokemons;

        DiccString<aed2::Nat> pokemonsCapturados;
    };

    struct infoPos {

        bool hayPokemon;

        Pokemon pokemon;

        aed2::Nat contadorCaptura;

        ColaPrior<TuplaOrd<Jugador, aed2::Nat> > jugsEsperandoCaptura;

        ConjuntoOrd<Jugador> jugsEnPos;
    };

    const Mapa _mapa;

    DiccString<aed2::Nat> _pokemons;

    aed2::Conj<Coordenada> _posConPokemons;

    aed2::Vector<infoJugador*> _jugadores;

    aed2::Arreglo<aed2::Arreglo<infoPos> > _grillaPos;

    aed2::Nat _cantPokemons;

    //AUX FUNCTIONS

    void AgregarACola(Jugador j);

    void RemoverDeCola(Jugador j);

    void ResetearContadores(Jugador j);


};


#endif //ALGO2_TP3_JUEGO_H
