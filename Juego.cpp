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
    while(!_basura.EsVacia()) {
        delete _basura.Primero();
        _basura.Fin();
    }
}

const Mapa &Juego::ObtenerMapa() const {
    return _mapa;
}

void Juego::AgregarPokemon(const Pokemon& pk, const Coordenada& c) {
    ++_cantPokemons;
    if (_pokemons.Definido(pk)){
        aed2::Nat nuevaCant = _pokemons.Obtener(pk) + 1;
        _pokemons.Definir(pk, nuevaCant);
    } else {
        _pokemons.Definir(pk, 1);
    }
    _grillaPos[c.latitud][c.longitud].hayPokemon = true;
    _grillaPos[c.latitud][c.longitud].pokemon = pk;
    _grillaPos[c.latitud][c.longitud].contadorCaptura = 0;
    _grillaPos[c.latitud][c.longitud].jugsEsperandoCaptura = new ColaPrior<TuplaOrd<Jugador, aed2::Nat> >();
    _basura.AgregarAdelante(_grillaPos[c.latitud][c.longitud].jugsEsperandoCaptura);
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c, 2);
    aed2::Conj<Coordenada>::Iterador itCoor = coorEnRango.CrearIt();
    while (itCoor.HaySiguiente()){

        Coordenada d = itCoor.Siguiente();
        ConjuntoOrd<Jugador>::const_Iterador it = _grillaPos[d.latitud][d.longitud].jugsEnPos.CrearIt();
        while (it.HayMas()) {
            Jugador jug = it.Actual();
            TuplaOrd<Jugador, aed2::Nat> tuplaJug(jug , _jugadores[jug]->cantPokemons);
            _grillaPos[c.latitud][c.longitud].jugsEsperandoCaptura->Encolar(tuplaJug);
            it.Avanzar();
        }
        itCoor.Avanzar();
    }
    _posConPokemons.AgregarRapido(c);
}

aed2::Nat Juego::AgregarJugador() {
    aed2::Nat res = _jugadores.Longitud();
    infoJugador* jugador = new infoJugador();
    _jugadores.AgregarAtras(jugador);
    return res;
}

void Juego::Conectarse(const Jugador& j, const Coordenada& c) {
    _jugadores[j]->conectado = true;
    _jugadores[j]->posicion = c;
    _grillaPos[c.latitud][c.longitud].jugsEnPos.Agregar(j);
    AgregarACola(j);
    ResetearContadores(j);
}

void Juego::Desconectarse(const Jugador& j) {
    Coordenada c = _jugadores[j]->posicion;
    _jugadores[j]->conectado = false;
    _grillaPos[c.latitud][c.longitud].jugsEnPos.Borrar(j);
    RemoverDeCola(j);
}

void Juego::Moverse(const Jugador& j, const Coordenada& c) {
    Coordenada posAnterior = _jugadores[j]->posicion;
    if(!_mapa.HayCamino(posAnterior, c) || Coordenada::DistEuclidea(posAnterior, c) > 100){
        _jugadores[j]->sanciones++;
        if (_jugadores[j]->sanciones == 5) {
            DiccString<aed2::Nat>::const_Iterador pokesABorrar = _jugadores[j]->pokemonsCapturados.CrearIt();
            while (pokesABorrar.HaySiguiente()) {
                DiccString<aed2::Nat>::Entrada sig(pokesABorrar.Siguiente());
                aed2::Nat nuevaCant = _pokemons.Obtener(sig.clave) - sig.valor;
                if (nuevaCant == 0) {
                    _pokemons.Borrar(sig.clave);
                } else {
                    _pokemons.Definir(sig.clave, nuevaCant);
                }
                _cantPokemons = _cantPokemons - sig.valor;
                pokesABorrar.Avanzar();
            }
        }
    } else {
        _grillaPos[posAnterior.latitud][posAnterior.longitud].jugsEnPos.Borrar(j);
        RemoverDeCola(j);
        _jugadores[j]->posicion = c;
        AgregarACola(j);
        _grillaPos[c.latitud][c.longitud].jugsEnPos.Agregar(j);
        aed2::Conj<Coordenada>::Iterador itPos = _posConPokemons.CrearIt();
        while (itPos.HaySiguiente()) {
            Coordenada coorConPk = itPos.Siguiente();
            if (Coordenada::DistEuclidea(c, coorConPk) > 4) {
                _grillaPos[coorConPk.latitud][coorConPk.longitud].contadorCaptura++;
                infoPos &posPk = _grillaPos[coorConPk.latitud][coorConPk.longitud];
                if (posPk.contadorCaptura == 10 && !posPk.jugsEsperandoCaptura->Vacia()) {
                    Pokemon pk = posPk.pokemon;
                    Jugador captor = posPk.jugsEsperandoCaptura->Proximo().first();
                    _jugadores[captor]->cantPokemons++;
                    if (_jugadores[captor]->pokemonsCapturados.Definido(pk)) {
                        aed2::Nat nuevaCant = _jugadores[captor]->pokemonsCapturados.Obtener(pk) + 1;
                        _jugadores[captor]->pokemonsCapturados.Definir(pk, nuevaCant);
                    } else {
                        _jugadores[captor]->pokemonsCapturados.Definir(pk, 1);
                    }
                    posPk.hayPokemon = false;
                    itPos.EliminarSiguiente();
                } else {
                    itPos.Avanzar();
                }
            } else {
                if (Coordenada::DistEuclidea(posAnterior, coorConPk) > 4) {
                    _grillaPos[coorConPk.latitud][coorConPk.longitud].contadorCaptura = 0;
                }
                itPos.Avanzar();
            }
        }
    }
}

bool Juego::EstaConectado(const Jugador& j) const {
    return _jugadores[j]->conectado;
}

aed2::Nat Juego::Sanciones(const Jugador& j) const {
    return _jugadores[j]->sanciones;
}

const Coordenada& Juego::Posicion(const Jugador& j) const {
    return _jugadores[j]->posicion;
}

DiccString<aed2::Nat>::const_Iterador Juego::Pokemons(const Jugador& j) const {
    return _jugadores[j]->pokemonsCapturados.CrearIt();
}

const aed2::Conj<Coordenada> &Juego::PosConPokemons() const {
    return _posConPokemons;
}

const Pokemon &Juego::PokemonEnPos(const Coordenada& c) const {
    return _grillaPos[c.latitud][c.longitud].pokemon;
}

bool Juego::PuedoAgregarPokemon(const Coordenada& c) const {
    return _mapa.PosExistente(c) && !HayPokemonEnDistancia(c,5);
}

bool Juego::HayPokemonCercano(const Coordenada& c) const {
    return HayPokemonEnDistancia(c,2);
}

Coordenada Juego::PosPokemonCercano(const Coordenada& c) const {
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c,2);
    aed2::Conj<Coordenada>::const_Iterador itCoor = coorEnRango.CrearIt();
    Coordenada coorPokemon(0,0);
    while(itCoor.HaySiguiente()){
        Coordenada siguiente = itCoor.Siguiente();
        if(HayPokemonEnPos(siguiente)){
            coorPokemon = siguiente;
        }
        itCoor.Avanzar();
    }
    return coorPokemon;
}

aed2::Conj<Jugador> Juego::EntrenadoresPosibles(const aed2::Conj<Jugador>& es, const Coordenada& c) const {
    aed2::Conj<Jugador> conjJug;
    ColaPrior<TuplaOrd<Jugador, aed2::Nat > >::const_Iterador itEntrenadores;
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c, 2);
    aed2::Conj<Coordenada>::Iterador itCoor = coorEnRango.CrearIt();
    while (itCoor.HaySiguiente()) {
        Coordenada siguiente = itCoor.Siguiente();
        if (HayPokemonEnPos(siguiente)) {
            itEntrenadores = _grillaPos[siguiente.latitud][siguiente.longitud].jugsEsperandoCaptura->CrearIt();
        }
        itCoor.Avanzar();
    }


    while(itEntrenadores.HayMas()){
        Jugador actual = itEntrenadores.Actual().first();
        if (es.Pertenece(actual)){
            conjJug.AgregarRapido(actual);
        }
        itEntrenadores.Avanzar();
    }
    return conjJug;
}

aed2::Nat Juego::IndiceRareza(const Pokemon& pk) const {
    aed2::Nat cantPk = 100 - (CantMismaEspecie(pk)*100/_cantPokemons);
    return cantPk;
}

aed2::Nat Juego::CantPokemonsTotales() const {
    return _cantPokemons;
}

aed2::Nat Juego::CantMismaEspecie(const Pokemon& pk) const {
    return _pokemons.Obtener(pk);
}

void Juego::AgregarACola(const Jugador& j) {
    Coordenada c = _jugadores[j]->posicion;
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c, 2);
    aed2::Conj<Coordenada>::const_Iterador itCoor;
    for(itCoor = coorEnRango.CrearIt(); itCoor.HaySiguiente(); itCoor.Avanzar()) {
        Coordenada siguiente = itCoor.Siguiente();
        if(HayPokemonEnPos(siguiente) && _mapa.HayCamino(c, siguiente)) {
            TuplaOrd<Jugador, aed2::Nat> tuplaJug(j, _jugadores[j]->cantPokemons);
            _grillaPos[siguiente.latitud][siguiente.longitud].jugsEsperandoCaptura->Encolar(tuplaJug);
        }
    }
}

void Juego::RemoverDeCola(const Jugador& j) {
    Coordenada c = _jugadores[j]->posicion;
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c,2);
    aed2::Conj<Coordenada>::const_Iterador itCoor;
    for(itCoor = coorEnRango.CrearIt(); itCoor.HaySiguiente(); itCoor.Avanzar()){
        Coordenada siguiente = itCoor.Siguiente();
        if(HayPokemonEnPos(siguiente) && _mapa.HayCamino(c, siguiente)) {
            TuplaOrd<Jugador, aed2::Nat> tuplaJug(j, _jugadores[j]->cantPokemons);
            _grillaPos[siguiente.latitud][siguiente.longitud].jugsEsperandoCaptura->Borrar(tuplaJug);
        }
    }
}

void Juego::ResetearContadores(const Jugador& j) {
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


aed2::Conj<Coordenada> Juego::PosicionesEnRango(const Coordenada& c, const aed2::Nat& n) const {
    aed2::Conj<Coordenada> conjRes;
    for(aed2::Nat i = 0; i <= n; i++){
        for (aed2::Nat j = 0; j <= n; j++){
            Coordenada ne(c.latitud + i, c.longitud + j);
            if (Coordenada::DistEuclidea(ne, c) <= n*n && _mapa.PosExistente(ne)){
                conjRes.Agregar(ne);
            }
            if (c.longitud >= j){
                Coordenada no(c.latitud + i, c.longitud - j);
                if (Coordenada::DistEuclidea(no, c) <= n*n && _mapa.PosExistente(no)){
                    conjRes.Agregar(no);
                }
            }
            if (c.latitud >= i){
                Coordenada se(c.latitud - i, c.longitud + j);
                if (Coordenada::DistEuclidea(se, c) <= n*n && _mapa.PosExistente(se)){
                    conjRes.Agregar(se);
                }
            }
            if (c.longitud >= j && c.latitud >= i){
                Coordenada so(c.latitud - i, c.longitud - j);
                if (Coordenada::DistEuclidea(so, c) <= n*n && _mapa.PosExistente(so)){
                    conjRes.Agregar(so);
                }
            }
        }
    }
    return conjRes;
}

bool Juego::HayPokemonEnPos(const Coordenada& c) const {
    return _grillaPos[c.latitud][c.longitud].hayPokemon;
}

// ITERADOR DE JUGADORES

Juego::const_itJugadores Juego::Jugadores() const {
    return Juego::const_itJugadores(&_jugadores, false);
}

Juego::const_itJugadores Juego::Expulsados() const {
    return Juego::const_itJugadores(&_jugadores, true);
}

bool Juego::HayPokemonEnDistancia(const Coordenada& c, const aed2::Nat& n) const {
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

Juego::const_itJugadores::const_itJugadores() {
}

Jugador Juego::const_itJugadores::Actual() const {
    for(Jugador i = _contador; i < _listaJugadores->Longitud(); ++i) {
        if(((*_listaJugadores)[i]->sanciones < 5) != _eliminados) {
            return i;
        }
    }
    return _listaJugadores->Longitud();
}

bool Juego::const_itJugadores::HayMas() const {
    return Actual() < _listaJugadores->Longitud();
}

void Juego::const_itJugadores::Avanzar() {
    _contador = Actual() + 1;
}

Juego::const_itJugadores::const_itJugadores(const aed2::Vector<infoJugador*>* jugadores, bool eliminados)
        : _listaJugadores(jugadores), _contador(0), _eliminados(eliminados) {
}
