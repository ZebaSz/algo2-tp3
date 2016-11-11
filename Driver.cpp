#include "Driver.h"

// Instanciar un mapa y un juego 

Driver::Driver(const Conj< Coordenada > & cs)
{
}

Driver::~Driver()
{
}

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c)
{
}

Jugador Driver::agregarJugador() {
    return 0;
}

void Driver::conectarse(const Jugador &j, const Coordenada &c) {
}

void Driver::desconectarse(const Jugador &j) {
}

void Driver::moverse(const Jugador &j, const Coordenada &c) {
}

Conj<Coordenada> Driver::mapa() const {
    return Conj<Coordenada>();
}

bool Driver::hayCamino(const Coordenada &c1, const Coordenada &c2) const {
    return false;
}

bool Driver::posExistente(const Coordenada &c) const {
    return false;
}

Conj<Jugador> Driver::jugadores() const {
    return Conj<Jugador>();
}

bool Driver::estaConectado(const Jugador &j) const {
    return false;
}

Nat Driver::sanciones(const Jugador &j) const {
    return 0;
}

Coordenada Driver::posicion(const Jugador &j) const {
    return Coordenada(0, 0);
}

Dicc<Pokemon, Nat> Driver::pokemons(const Jugador &j) const {
    return Dicc<Pokemon, Nat>();
}

Conj<Jugador> Driver::expulsados() const {
    return Conj<Jugador>();
}

Conj<Coordenada> Driver::posConPokemons() const {
    return Conj<Coordenada>();
}

Pokemon Driver::pokemonEnPos(const Coordenada &c) const {
    return Pokemon();
}

Nat Driver::cantMovimientosParaCaptura(const Coordenada &c) const {
    return 0;
}

bool Driver::puedoAgregarPokemon(const Coordenada &c) const {
    return false;
}

bool Driver::hayPokemonCercano(const Coordenada &c) const {
    return false;
}

Coordenada Driver::posPokemonCercano(const Coordenada &c) const {
    return Coordenada(0, 0);
}

Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada &c) const {
    return Conj<Jugador>();
}

Nat Driver::indiceRareza(const Pokemon &p) const {
    return 0;
}

Nat Driver::cantPokemonsTotales() const {
    return 0;
}

Nat Driver::cantMismaEspecie(const Pokemon &p) const {
    return 0;
}


// TODO: Completar con el resto de las implementaciones