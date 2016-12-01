#ifndef ALGO2_TP3_JUEGO_H
#define ALGO2_TP3_JUEGO_H

#include "Mapa.h"
#include "TiposJuego.h"
#include "DiccString.h"
#include "ColaPrior.h"
#include "TuplaOrd.h"

class Juego {
friend class Driver;
friend class const_itJugadores;
struct infoJugador;
public:
    class const_itJugadores;

    Juego(const Mapa&);

    ~Juego();

    void AgregarPokemon(const Pokemon&, const Coordenada&);

    aed2::Nat AgregarJugador();

    void Conectarse(const Jugador&, const Coordenada&);

    void Desconectarse(const Jugador&);

    void Moverse(const Jugador&, const Coordenada&);

    const Mapa& ObtenerMapa() const;

    const_itJugadores Jugadores() const;

    bool EstaConectado(const Jugador&) const;

    aed2::Nat Sanciones(const Jugador&) const;

    const Coordenada& Posicion(const Jugador&) const;

    DiccString<aed2::Nat>::const_Iterador Pokemons(const Jugador&) const;

    const_itJugadores Expulsados() const;

    const aed2::Conj<Coordenada>& PosConPokemons() const;

    const Pokemon& PokemonEnPos(const Coordenada&) const;

    bool PuedoAgregarPokemon(const Coordenada&) const;

    bool HayPokemonCercano(const Coordenada&) const;

    Coordenada PosPokemonCercano(const Coordenada&) const;

    aed2::Conj<Jugador> EntrenadoresPosibles(const aed2::Conj<Jugador>&, const Coordenada&) const;

    aed2::Nat IndiceRareza(const Pokemon&) const;

    aed2::Nat CantPokemonsTotales() const;

    aed2::Nat CantMismaEspecie(const Pokemon&) const;

    class const_itJugadores {
    friend class Juego;
    public:
        const_itJugadores();

        Jugador Actual() const;

        bool HayMas() const;

        void Avanzar();

    private:
        const_itJugadores(const aed2::Vector<infoJugador*>*, bool);

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

        ColaPrior<TuplaOrd<Jugador, aed2::Nat> >* jugsEsperandoCaptura;

        ConjuntoOrd<Jugador> jugsEnPos;
    };

    const Mapa _mapa;

    DiccString<aed2::Nat> _pokemons;

    aed2::Conj<Coordenada> _posConPokemons;

    aed2::Vector<infoJugador*> _jugadores;

    aed2::Arreglo<aed2::Arreglo<infoPos> > _grillaPos;

    aed2::Nat _cantPokemons;

    aed2::Lista<ColaPrior <TuplaOrd <Jugador, aed2::Nat> >* > _basura;

    //AUX FUNCTIONS

    void AgregarACola(const Jugador&);

    void RemoverDeCola(const Jugador&);

    void ResetearContadores(const Jugador&);

    bool HayPokemonEnDistancia(const Coordenada&, const aed2::Nat&) const;

    bool HayPokemonEnPos(const Coordenada&) const;

    aed2::Conj<Coordenada> PosicionesEnRango(const Coordenada&, const aed2::Nat&) const;

};


#endif //ALGO2_TP3_JUEGO_H
