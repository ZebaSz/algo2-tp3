#include "Juego.h"

Juego::Juego(const Mapa& mapa) : _mapa(mapa) {
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
    //_grillaPos[c.latitud][c.longitud].jugsEsperandoCaptura; TODO ¿constructor vacio?
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
}

aed2::Nat Juego::AgregarJugador(){
    aed2::Nat result = _jugadores.Longitud();
    infoJugador* infoJ = new infoJugador;
    _jugadores.AgregarAtras(infoJ);
    return result;
}

void Juego::Conectarse(Jugador j, Coordenada c){
    _jugadores[j]->conectado = true;
    _jugadores[j]->posicion = c;
    _grillaPos[c.latitud][c.longitud].jugsEnPos.Agregar(j);
    AgregarACola(j);
    ResetearContadores(j);
}

void Juego::Desconectarse(Jugador j){
    _jugadores[j]->conectado = true;
    _grillaPos[_jugadores[j]->posicion.latitud][_jugadores[j]->posicion.longitud].jugsEnPos.Borrar(j);
    RemoverDeCola(j);
}

void Juego::Moverse(Jugador j, Coordenada c){
    Coordenada posAnterior = _jugadores[j]->posicion;
    _grillaPos[posAnterior.latitud][posAnterior.longitud].jugsEnPos.Borrar(j);
    RemoverDeCola(j);
    if(!_mapa.HayCamino(posAnterior, c) || posAnterior.DistEuclidea(c) > 100){
        _jugadores[j]->sanciones++;
    }
    if (_jugadores[j]->sanciones == 5){
        DiccString<aed2::Nat>::const_Iterador pokesABorrar = _jugadores[j]->pokemonsCapturados.CrearIt();
        while (pokesABorrar.HaySiguiente()){
            TuplaOrd<std::string, aed2::Nat> sig("corregime careta", 0); //TODO esto es pa que compile
            //TuplaOrd<std::string, aed2::Nat> sig = pokesABorrar.Siguiente(); //TODO el iterador solo saca el significado, no la clave.
            aed2::Nat nuevaCant = _pokemons.Obtener(sig.first()) - sig.second();
            if (nuevaCant == 0){
                _pokemons.Borrar(sig.first());
            } else {
                _pokemons.Definir(sig.first(), nuevaCant);
            }
            _cantPokemons = _cantPokemons - sig.second();
            pokesABorrar.Avanzar();
        }
    } else {
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

aed2::Conj<Coordenada> Juego::PosicionesEnRango (Coordenada c, aed2::Nat n){
    aed2::Conj<Coordenada> conjRes;
    int i;
    for(int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
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
}

void Juego::AgregarACola(Jugador j){

}

void Juego::RemoverDeCola(Jugador j){

}

void Juego::ResetearContadores(Jugador j){

}
