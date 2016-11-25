#include "Juego.h"

Juego::Juego(const Mapa& mapa) : _mapa(mapa), _grillaPos(mapa.Alto()), _cantPokemons(0) {
    for(aed2::Nat i = 0; i < mapa.Alto(); ++i) {
        _grillaPos.Definir(i, aed2::Arreglo<infoPos>(mapa.Ancho()));
        for(aed2::Nat j = 0; j < mapa.Ancho(); ++j) {
            _grillaPos[i].Definir(j, infoPos());
        }
    }
}

Juego::~Juego() {
    for(aed2::Nat i = 0; i < _jugadores.Longitud(); ++i) {
        delete _jugadores[i];
    }
}

const Mapa &Juego::ObtenerMapa() const {
    return _mapa;
}

void Juego::AgregarPokemon(Pokemon pk, Coordenada c) {
    /*
    _cantPokemons++;
    if(_pokemons.Definido(pk)){
        aed2::Nat nuevaCant = _pokemons.Obtener(pk) + 1;
        _pokemons.Definir(pk, nuevaCant);
    }else{
        _pokemons.Definir(pk, 1);
    }
    _grillaPos[c.latitud][c.longitud].hayPokemon = true;
    _grillaPos[c.latitud][c.longitud].pokemon = pk;
    _grillaPos[c.latitud][c.longitud].contadorCaptura = 0;
    //TODO: ACA HAY QUE BORRAR LA COLA ANTERIOR
     */
}

aed2::Nat Juego::AgregarJugador() {
    aed2::Nat res = _jugadores.Longitud();
    infoJugador* jugador = new infoJugador();
    _jugadores.AgregarAtras(jugador);
    return res;
}

void Juego::Conectarse(Jugador j, Coordenada c) {
    _jugadores[j]->conectado = true;
    _jugadores[j]->posicion = c;
    _grillaPos[c.latitud][c.longitud].jugsEnPos.Agregar(j);
    AgregarACola(j);
    ResetearContadores(j);
}

void Juego::Desconectarse(Jugador j) {
    Coordenada c = _jugadores[j]->posicion;
    _jugadores[j]->conectado = false;
    _grillaPos[c.latitud][c.longitud].jugsEnPos.Borrar(j);
}

void Juego::Moverse(Jugador j, Coordenada c) {
    // TODO implement this function
    assert(false);
}

bool Juego::EstaConectado(Jugador j) const {
    return _jugadores[j]->conectado;
}

aed2::Nat Juego::Sanciones(Jugador j) const {
    return _jugadores[j]->sanciones;
}

Coordenada Juego::Posicion(Jugador j) const {
    return _jugadores[j]->posicion;
}

const aed2::Conj<Coordenada> &Juego::PosConPokemons() const {
    return _posConPokemons;
}

const Pokemon &Juego::PokemonEnPos(Coordenada c) const {
    return _grillaPos[c.latitud][c.longitud].pokemon;
}

bool Juego::PuedoAgregarPokemon(Coordenada c) const {
    return _mapa.PosExistente(c);//TODO: && _mapa.HayPokemonEnDistancia(c, 5);
}

bool Juego::HayPokemonCercano(Coordenada c) const {
    // TODO implement this function
    assert(false);
}

Coordenada Juego::PosPokemonCercano(Coordenada c) const {
    // TODO implement this function
    assert(false);
}

aed2::Conj<Jugador> Juego::EntrenadoresPosibles(aed2::Conj<Jugador> es, Coordenada c) const {
    // TODO implement this function
    assert(false);
}

aed2::Nat Juego::IndiceRareza(Pokemon pk) const {
    // TODO implement this function
    assert(false);
}

aed2::Nat Juego::CantPokemonsTotales() const {
    // TODO implement this function
    assert(false);
}

aed2::Nat Juego::CantMismaEspecie(Pokemon pk) const {
    // TODO implement this function
    assert(false);
}

void Juego::AgregarACola(Jugador j) {
    Coordenada c = _jugadores[j]->posicion;
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c, 2);
    aed2::Conj<Coordenada>::const_Iterador itCoor = coorEnRango.CrearIt();
    while(itCoor.HaySiguiente()) {
        Coordenada siguiente = itCoor.Siguiente();
        if(HayPokemonEnPos(siguiente)) {
            _grillaPos[siguiente.latitud][siguiente.longitud].jugsEsperandoCaptura
                    .Encolar(TuplaOrd<Jugador, aed2::Nat>(j, _jugadores[j]->cantPokemons));
        }
        itCoor.Avanzar();
    }
}

void Juego::RemoverDeCola(Jugador j) {
    // TODO implement this function
    assert(false);
}

void Juego::ResetearContadores(Jugador j) {

    Coordenada c = _jugadores[j]->posicion;
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c, 2);
    aed2::Conj<Coordenada>::const_Iterador itCoor = coorEnRango.CrearIt();
    while(itCoor.HaySiguiente()) {
        Coordenada siguiente = itCoor.Siguiente();
        if(HayPokemonEnPos(siguiente)) {
            _grillaPos[siguiente.latitud][siguiente.longitud].contadorCaptura = 0;
        }
        itCoor.Avanzar();
    }
}

// ITERADOR DE JUGADORES

Juego::itJugadores Juego::jugadores() const {
    return Juego::itJugadores(&_jugadores, false);
}

Juego::itJugadores Juego::expulsados() const {
    return Juego::itJugadores(&_jugadores, true);
}

bool Juego::HayPokemonEnDistancia(Coordenada c, aed2::Nat n) const {
    bool res = false;
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c, n);
    aed2::Conj<Coordenada>::Iterador itCoor = coorEnRango.CrearIt();
    while (itCoor.HaySiguiente()) {
        Coordenada siguiente = itCoor.Siguiente();
        if (HayPokemonEnPos(siguiente)) {
            res = true;
        }
        itCoor.Avanzar();
    }
    return res;
}

aed2::Conj<Coordenada> Juego::PosicionesEnRango(Coordenada c, aed2::Nat n) const {
    aed2::Conj<Coordenada> res;
    for(aed2::Nat i = 0; i < n; ++i) {
        for(aed2::Nat j = 0; j < n; ++j) {
            Coordenada ne = Coordenada(c.latitud + i, c.longitud + j);
            if (Disteuclidea(c, ne) <= n*n && _mapa.PosExistente(ne)) {
             res.AgregarRapido(ne);
            }
            if (c.longitud > j) {
                Coordenada no = Coordenada(c.latitud + i, c.longitud - j);
                if (Disteuclidea(c, no) <= n*n && _mapa.PosExistente(no)) {
                    res.AgregarRapido(no);
                }
            }
            if (c.latitud > i) {
                Coordenada se = Coordenada(c.latitud - i, c.longitud + j);
                if (Disteuclidea(c, se) <= n*n && _mapa.PosExistente(se)) {
                    res.AgregarRapido(se);
                }
            }
            if (c.latitud > i && c.longitud > j) {
                Coordenada so = Coordenada(c.latitud - i, c.longitud - j);
                if (Disteuclidea(c, so) <= n*n && _mapa.PosExistente(so)) {
                    res.AgregarRapido(so);
                }
            }
        }
    }
    return res;
}

bool Juego::HayPokemonEnPos(Coordenada c) const {
    return _grillaPos[c.latitud][c.longitud].hayPokemon;
}

aed2::Nat Juego::Disteuclidea(Coordenada c1, Coordenada c2) const {
    aed2::Nat  la = 0;
    aed2::Nat  lo = 0;
    if (c1.latitud > c2.latitud){
        la = (c1.latitud - c2.latitud) * (c1.latitud - c2.latitud);
    } else {
        la = (c2.latitud - c1.latitud) * (c2.latitud - c1.latitud);
    }
    if (c1.longitud > c2.longitud){
        la = (c1.longitud - c2.longitud) * (c1.longitud - c2.longitud);
    } else {
        la = (c2.longitud - c1.longitud) * (c2.longitud - c1.longitud);
    }
    return la + lo;
}


Juego::itJugadores::itJugadores() {
}

Jugador Juego::itJugadores::Actual() {
    for(Jugador i = _contador; i < _listaJugadores->Longitud(); ++i) {
        if(((*_listaJugadores)[i]->sanciones < 5) != _eliminados) {
            return i;
        }
    }
    return 0;
}

bool Juego::itJugadores::HayMas() {
    bool res = false;
    for(Jugador i = _contador; i < _listaJugadores->Longitud(); ++i) {
        if(((*_listaJugadores)[i]->sanciones < 5) != _eliminados) {
            res = true;
            break;
        }
    }
    return res;
}

void Juego::itJugadores::Avanzar() {
    for(Jugador i = _contador; i < _listaJugadores->Longitud(); ++i) {
        if(((*_listaJugadores)[i]->sanciones < 5) != _eliminados) {
            _contador = i + 1;
            break;
        }
    }
}

Juego::itJugadores::itJugadores(const aed2::Vector<infoJugador*>* jugadores, bool eliminados)
        : _listaJugadores(jugadores), _contador(0), _eliminados(eliminados) {
}
