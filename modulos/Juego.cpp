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
    _grillaPos[c.latitud][c.longitud].jugsEsperandoCaptura = ColaPrior< TuplaOrd<Jugador, aed2::Nat> >();
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c, 2);
    aed2::Conj<Coordenada>::Iterador itCoor = coorEnRango.CrearIt();
    while (itCoor.HaySiguiente()){
        Coordenada d = itCoor.Siguiente();
        ConjuntoOrd<Jugador>::const_Iterador it = _grillaPos[d.latitud][d.longitud].jugsEnPos.CrearIt();
        while (it.HayMas()) {
            Jugador jug = it.Actual();
            TuplaOrd<Jugador, aed2::Nat> tuplaJug(jug , _jugadores[jug]->cantPokemons);
            _grillaPos[c.latitud][c.longitud].jugsEsperandoCaptura.Encolar(tuplaJug);
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
    Coordenada posAnterior = _jugadores[j]->posicion;
    if(!_mapa.HayCamino(posAnterior, c) || posAnterior.DistEuclidea(c) > 100){
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
    }
    aed2::Conj<Coordenada>::Iterador itPos = _posConPokemons.CrearIt();
    while(itPos.HaySiguiente()){
        Coordenada coorConPk = itPos.Siguiente();
        if (c.DistEuclidea(coorConPk) > 4){
            _grillaPos[coorConPk.latitud][coorConPk.longitud].contadorCaptura++;
            infoPos posPk = _grillaPos[coorConPk.latitud][coorConPk.longitud];
            if (posPk.contadorCaptura == 10){
                Pokemon pk = posPk.pokemon;
                Jugador captor = posPk.jugsEsperandoCaptura.Proximo().first();
                _jugadores[captor]->cantPokemons++;
                if (_jugadores[captor]->pokemonsCapturados.Definido(pk)){
                    aed2::Nat nuevaCant =_jugadores[captor]->pokemonsCapturados.Obtener(pk) + 1;
                    _jugadores[captor]->pokemonsCapturados.Definir(pk, nuevaCant);
                } else {
                    _jugadores[captor]->pokemonsCapturados.Definir(pk, 1);
                }
                itPos.EliminarSiguiente();
            } else{
                itPos.Avanzar();
            }
        } else{
            if (posAnterior.DistEuclidea(coorConPk) > 4){
                _grillaPos[coorConPk.latitud][coorConPk.longitud].contadorCaptura = 0;
            }
            itPos.Avanzar();
        }
    }
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

DiccString<aed2::Nat>::const_Iterador Juego::Pokemons(Jugador j) const {
    return _jugadores[j]->pokemonsCapturados.CrearIt();
}

const aed2::Conj<Coordenada> &Juego::PosConPokemons() const {
    return _posConPokemons;
}

const Pokemon &Juego::PokemonEnPos(Coordenada c) const {
    return _grillaPos[c.latitud][c.longitud].pokemon;
}

bool Juego::PuedoAgregarPokemon(Coordenada c) const {
    return (_mapa.PosExistente(c) && HayPokemonEnDistancia(c,5));
}

bool Juego::HayPokemonCercano(Coordenada c) const {
    return HayPokemonEnDistancia(c,2);
}

Coordenada Juego::PosPokemonCercano(Coordenada c) const {
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

aed2::Conj<Jugador> Juego::EntrenadoresPosibles(aed2::Conj<Jugador> es, Coordenada c) const {
    aed2::Conj<Jugador> conjJug;
    ColaPrior<TuplaOrd<Jugador, aed2::Nat > >::const_Iterador itEntrenadores = _grillaPos[c.latitud][c.longitud].jugsEsperandoCaptura.CrearIt();
    while(itEntrenadores.HayMas()){
        Jugador actual = itEntrenadores.Actual().first();
        if (es.Pertenece(actual)){
            conjJug.AgregarRapido(actual);
        }
    }
    return conjJug;
}

aed2::Nat Juego::IndiceRareza(Pokemon pk) const {
    aed2::Nat cantPk = 100 - (CantMismaEspecie(pk)*100/_cantPokemons);
    return cantPk;
}

aed2::Nat Juego::CantPokemonsTotales() const {
    return _cantPokemons;
}

aed2::Nat Juego::CantMismaEspecie(Pokemon pk) const {
    return _pokemons.Obtener(pk);
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
    Coordenada c = _jugadores[j]->posicion;
    aed2::Conj<Coordenada> coorEnRango = PosicionesEnRango(c,2);
    aed2::Conj<Coordenada>::const_Iterador itCoor = coorEnRango.CrearIt();
    while (itCoor.HaySiguiente()){
        Coordenada siguiente = itCoor.Siguiente();
        if (HayPokemonEnPos(siguiente)){
            TuplaOrd<Jugador, aed2::Nat> tuplaJug(j, _jugadores[j]->cantPokemons);
            _grillaPos[siguiente.latitud][siguiente.longitud].jugsEsperandoCaptura.Borrar(tuplaJug);
        }
        itCoor.Avanzar();
    }
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


aed2::Conj<Coordenada> Juego::PosicionesEnRango(Coordenada c, aed2::Nat n) const {
    aed2::Conj<Coordenada> conjRes;
    for(aed2::Nat i = 0; i < n; i++){
        for (aed2::Nat j = 0; j < n; j++){
            Coordenada ne(c.latitud + i, c.longitud + j);
            if (ne.DistEuclidea(c) <= n*n && _mapa.PosExistente(ne)){
                conjRes.AgregarRapido(ne);
            }
            if (c.longitud > j){
                Coordenada no(c.latitud + i, c.longitud - j);
                if (no.DistEuclidea(c) <= n*n && _mapa.PosExistente(no)){
                    conjRes.AgregarRapido(no);
                }
            }
            if (c.latitud > i){
                Coordenada se(c.latitud - i, c.longitud + j);
                if (se.DistEuclidea(c) <= n*n && _mapa.PosExistente(se)){
                    conjRes.AgregarRapido(se);
                }
            }
            if (c.longitud > j && c.latitud > i){
                Coordenada so(c.latitud - i, c.longitud - j);
                if (so.DistEuclidea(c) <= n*n && _mapa.PosExistente(so)){
                    conjRes.AgregarRapido(so);
                }
            }
        }
    }
    return conjRes;
}

bool Juego::HayPokemonEnPos(Coordenada c) const {
    return _grillaPos[c.latitud][c.longitud].hayPokemon;
}

// ITERADOR DE JUGADORES

Juego::itJugadores Juego::Jugadores() const {
    return Juego::itJugadores(&_jugadores, false);
}

Juego::itJugadores Juego::Expulsados() const {
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
