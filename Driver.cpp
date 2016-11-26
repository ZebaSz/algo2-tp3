#include "Driver.h"

// Instanciar un Mapa y un juego

Driver::Driver(const Conj< Coordenada > & cs) : _juego(conjAMapa(cs))
{
}

Driver::~Driver()
{
}

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c) {
    _juego.AgregarPokemon(p, c);
}

Jugador Driver::agregarJugador() {
    return _juego.AgregarJugador();
}

void Driver::conectarse(const Jugador &j, const Coordenada &c) {
    _juego.Conectarse(j, c);
}

void Driver::desconectarse(const Jugador &j) {
    _juego.Desconectarse(j);
}

void Driver::moverse(const Jugador &j, const Coordenada &c) {
    _juego.Moverse(j, c);
}

Conj<Coordenada> Driver::mapa() const {
    return _juego.ObtenerMapa().Coordenadas();
}

bool Driver::hayCamino(const Coordenada &c1, const Coordenada &c2) const {
    return _juego.ObtenerMapa().HayCamino(c1, c2);
}

bool Driver::posExistente(const Coordenada &c) const {
    return _juego.ObtenerMapa().PosExistente(c);
}

Conj<Jugador> Driver::jugadores() const {
    Conj<Jugador> res;

    Juego::itJugadores it;
    for(it = _juego.Jugadores(); it.HayMas(); it.Avanzar()) {
        res.AgregarRapido(it.Actual());
    }
    return res;
}

bool Driver::estaConectado(const Jugador &j) const {
    return _juego.EstaConectado(j);
}

Nat Driver::sanciones(const Jugador &j) const {
    return _juego.Sanciones(j);
}

Coordenada Driver::posicion(const Jugador &j) const {
    return _juego.Posicion(j);
}

Dicc<Pokemon, Nat> Driver::pokemons(const Jugador &j) const {
    Dicc<Pokemon, Nat> res;
    DiccString<Nat>::const_Iterador it;
    for(it = _juego.Pokemons(j); it.HaySiguiente(); it.Avanzar()) {
        res.Definir(it.Siguiente().clave, it.Siguiente().valor);
    }
    return res;
}

Conj<Jugador> Driver::expulsados() const {
    Conj<Jugador> res;

    Juego::itJugadores it;
    for(it = _juego.Expulsados(); it.HayMas(); it.Avanzar()) {
        res.AgregarRapido(it.Actual());
    }
    return res;
}

Conj<Coordenada> Driver::posConPokemons() const {
    return _juego.PosConPokemons();
}

Pokemon Driver::pokemonEnPos(const Coordenada &c) const {
    return _juego.PokemonEnPos(c);
}

Nat Driver::cantMovimientosParaCaptura(const Coordenada &c) const {
    return _juego._grillaPos[c.latitud][c.longitud].contadorCaptura;
}

bool Driver::puedoAgregarPokemon(const Coordenada &c) const {
    return _juego.PuedoAgregarPokemon(c);
}

bool Driver::hayPokemonCercano(const Coordenada &c) const {
    return _juego.HayPokemonCercano(c);
}

Coordenada Driver::posPokemonCercano(const Coordenada &c) const {
    return _juego.PosPokemonCercano(c);
}

Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada &c) const {
    return _juego.EntrenadoresPosibles(jugadores(), c);
}

Nat Driver::indiceRareza(const Pokemon &p) const {
    return _juego.IndiceRareza(p);
}

Nat Driver::cantPokemonsTotales() const {
    return _juego.CantPokemonsTotales();
}

Nat Driver::cantMismaEspecie(const Pokemon &p) const {
    return _juego.CantMismaEspecie(p);
}

Mapa Driver::conjAMapa(const Conj<Coordenada>& cs) {
    Mapa mapa;
    Conj<Coordenada>::const_Iterador it;
    for(it = cs.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        mapa.AgregarCoor(it.Siguiente());
    }
    return mapa;
}