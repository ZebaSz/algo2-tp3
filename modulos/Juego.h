#ifndef ALGO2_TP3_JUEGO_H
#define ALGO2_TP3_JUEGO_H

#include "Mapa.h"
#include "../TiposJuego.h"
#include "DiccString.h"
#include "ColaPrior.h"
#include "TuplaOrd.h"

class Juego {
friend class Driver;
friend class itJugadores;
struct infoJugador;
public:
    class itJugadores;

    Juego(const Mapa&);

    ~Juego();

    void AgregarPokemon(Pokemon pk,Coordenada c);

    aed2::Nat AgregarJugador();

    void Conectarse(Jugador j, Coordenada c);

    void Desconectarse(Jugador j);

    void Moverse(Jugador j, Coordenada c);

    const Mapa& ObtenerMapa() const;

    itJugadores Jugadores() const;

    bool EstaConectado(Jugador j) const;

    aed2::Nat Sanciones(Jugador j) const;

    Coordenada Posicion(Jugador j) const;

    DiccString<aed2::Nat>::const_Iterador Pokemons(Jugador j) const;

    itJugadores Expulsados() const;

    const aed2::Conj<Coordenada>& PosConPokemons() const;

    const Pokemon& PokemonEnPos(Coordenada c) const;

    bool PuedoAgregarPokemon(Coordenada c) const;

    bool HayPokemonCercano(Coordenada c) const;

    Coordenada PosPokemonCercano(Coordenada c) const;

    aed2::Conj<Jugador> EntrenadoresPosibles(aed2::Conj<Jugador> es, Coordenada c) const;

    aed2::Nat IndiceRareza(Pokemon pk) const;

    aed2::Nat CantPokemonsTotales() const;

    aed2::Nat CantMismaEspecie(Pokemon pk) const;

    class itJugadores {
    friend class Juego;
    public:
        itJugadores();

        Jugador Actual();

        bool HayMas();

        void Avanzar();

    private:
        itJugadores(const aed2::Vector<infoJugador*>*, bool);

        const aed2::Vector<infoJugador*>* _listaJugadores;
        aed2::Nat _contador;
        bool _eliminados;
    };


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

    bool HayPokemonEnDistancia(Coordenada c, aed2::Nat n) const;

    bool HayPokemonEnPos(Coordenada c) const;

    aed2::Conj<Coordenada> PosicionesEnRango(Coordenada coor, aed2::Nat n) const;

};


#endif //ALGO2_TP3_JUEGO_H
