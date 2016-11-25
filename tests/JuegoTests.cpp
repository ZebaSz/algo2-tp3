#include "gtest/gtest.h"
#include "../aed2/Conj.h"
#include "../Juego.h"

// --------- FIXTURES ---------

class JuegoTest : public ::testing::Test {
public:
    JuegoTest() : c1(0,0), c2(1,2), c3(10,0), c4(1,3) {}
protected:
    virtual void SetUp() {
        cc.Agregar(c1);
        cc.Agregar(Coordenada(0,1));
        cc.Agregar(Coordenada(0,2));
        cc.Agregar(c2);
        cc.Agregar(c3);
        cc.Agregar(c4);
        cc.Agregar(Coordenada(1,4));
        aed2::Conj<Coordenada>::const_Iterador it;
        for(it = cc.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
            m.AgregarCoor(it.Siguiente());
        }
    }

    void expulsar(Juego& j, const Jugador e) {
        while(j.Sanciones(e) < aed2::Nat(5)) {
            if(j.Posicion(e) == c1) {
                j.Moverse(e, c3);
            } else {
                j.Moverse(e, c1);
            }
        }
    }

    Mapa m;
    Coordenada c1;
    Coordenada c2;
    Coordenada c3;
    Coordenada c4;
    aed2::Conj<Coordenada> cc;

    Juego::itJugadores itJug;
};

// --------- TESTS ---------

TEST_F(JuegoTest, coordenadasMapa) {
    Juego j(m);
    ASSERT_EQ(j.ObtenerMapa().Coordenadas(), m.Coordenadas());
}

TEST_F(JuegoTest, agregarJugadores) {
    Juego j(m);
    ASSERT_EQ(j.AgregarJugador(), aed2::Nat(0));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.AgregarJugador(), aed2::Nat(1));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(1)));
    ASSERT_EQ(j.AgregarJugador(), aed2::Nat(2));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(1)));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(2)));
}

TEST_F(JuegoTest, agregarPokemones){
    Juego j(m);
    ASSERT_TRUE(j.PosConPokemons().EsVacio());
    j.AgregarPokemon("pikachu", c1);
    ASSERT_EQ(j.CantPokemonsTotales(), aed2::Nat(1));
    ASSERT_EQ(j.PokemonEnPos(c1), "pikachu");
    ASSERT_EQ(j.PosConPokemons().Cardinal(), aed2::Nat(1));
    ASSERT_TRUE(j.PosConPokemons().Pertenece(c1));
    j.AgregarPokemon("squirtle", c3);
    ASSERT_EQ(j.CantPokemonsTotales(), aed2::Nat(2));
    ASSERT_EQ(j.PokemonEnPos(c3), "squirtle");
    ASSERT_EQ(j.PokemonEnPos(c1), "pikachu");
    ASSERT_EQ(j.PosConPokemons().Cardinal(), aed2::Nat(2));
    ASSERT_TRUE(j.PosConPokemons().Pertenece(c1));
    ASSERT_TRUE(j.PosConPokemons().Pertenece(c3));
}

TEST_F(JuegoTest, conectarIgualdad) {
    Juego j(m);
    ASSERT_EQ(j.AgregarJugador(), aed2::Nat(0));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(0)));
    j.Conectarse(aed2::Nat(0), c1);
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Posicion(aed2::Nat(0)), c1);
    j.Desconectarse(aed2::Nat(0));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.AgregarJugador(), aed2::Nat(1));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(1)));
    j.Conectarse(aed2::Nat(1), c1);
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(1)));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Posicion(aed2::Nat(1)), c1);
    j.Conectarse(aed2::Nat(0), c3);
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Posicion(aed2::Nat(0)), c3);
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(1)));
    ASSERT_EQ(j.Posicion(aed2::Nat(1)), c1);
    j.Desconectarse(aed2::Nat(1));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(1)));
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Posicion(aed2::Nat(0)), c3);
    j.Desconectarse(aed2::Nat(0));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(1)));

}


TEST_F(JuegoTest, pitanaSancionar) {
    Juego j(m);
    Jugador jug1 = j.AgregarJugador();
    Jugador jug2 = j.AgregarJugador();

    j.Conectarse(jug1, c1);
    ASSERT_TRUE(j.EstaConectado(jug1));
    ASSERT_EQ(j.Posicion(jug1), c1);
    ASSERT_EQ(j.Sanciones(jug1), aed2::Nat(0));
    j.Conectarse(jug2, c2);
    ASSERT_TRUE(j.EstaConectado(jug2));
    ASSERT_EQ(j.Posicion(jug2), c2);
    ASSERT_EQ(j.Sanciones(jug2), aed2::Nat(0));

    j.Moverse(jug1, c3);
    ASSERT_TRUE(j.EstaConectado(jug1));
    ASSERT_EQ(j.Posicion(jug1), c1);
    ASSERT_EQ(j.Sanciones(jug1), aed2::Nat(1));
    j.Moverse(jug2, c1);
    ASSERT_TRUE(j.EstaConectado(jug2));
    ASSERT_EQ(j.Posicion(jug2), c1);
    ASSERT_EQ(j.Sanciones(jug2), aed2::Nat(0));

    j.Moverse(jug1, c3);
    ASSERT_TRUE(j.EstaConectado(jug1));
    ASSERT_EQ(j.Posicion(jug1), c1);
    ASSERT_EQ(j.Sanciones(jug1), aed2::Nat(2));
    j.Moverse(jug2, c4);
    ASSERT_TRUE(j.EstaConectado(jug2));
    ASSERT_EQ(j.Posicion(jug2), c4);
    ASSERT_EQ(j.Sanciones(jug2), aed2::Nat(0));

    j.Moverse(jug1, c1);
    ASSERT_TRUE(j.EstaConectado(jug1));
    ASSERT_EQ(j.Posicion(jug1), c1);
    ASSERT_EQ(j.Sanciones(jug1), aed2::Nat(2));
    j.Moverse(jug2, c3);
    ASSERT_TRUE(j.EstaConectado(jug2));
    ASSERT_EQ(j.Posicion(jug2), c4);
    ASSERT_EQ(j.Sanciones(jug2), aed2::Nat(1));

    j.Moverse(jug1, c3);
    ASSERT_TRUE(j.EstaConectado(jug1));
    ASSERT_EQ(j.Posicion(jug1), c1);
    ASSERT_EQ(j.Sanciones(jug1), aed2::Nat(3));
    j.Moverse(jug2, c2);
    ASSERT_TRUE(j.EstaConectado(jug2));
    ASSERT_EQ(j.Posicion(jug2), c2);
    ASSERT_EQ(j.Sanciones(jug2), aed2::Nat(1));

    j.Moverse(jug1, c3);
    ASSERT_TRUE(j.EstaConectado(jug1));
    ASSERT_EQ(j.Posicion(jug1), c1);
    ASSERT_EQ(j.Sanciones(jug1), aed2::Nat(4));
    j.Moverse(jug2, c3);
    ASSERT_TRUE(j.EstaConectado(jug2));
    ASSERT_EQ(j.Posicion(jug2), c2);
    ASSERT_EQ(j.Sanciones(jug2), aed2::Nat(2));

    j.Moverse(jug1, c3);
    ASSERT_EQ(j.Sanciones(jug1), aed2::Nat(5));
    ASSERT_TRUE(j.EstaConectado(jug2));
    ASSERT_EQ(j.Posicion(jug2), c2);
    ASSERT_EQ(j.Sanciones(jug2), aed2::Nat(2));
}

TEST_F(JuegoTest, puedoAgregarPokemon) {
    Juego j(m);
    ASSERT_FALSE(j.PuedoAgregarPokemon(Coordenada(11, 11)));
    ASSERT_FALSE(j.PuedoAgregarPokemon(Coordenada(0, 10)));
    ASSERT_TRUE(j.PuedoAgregarPokemon(c1));
    ASSERT_TRUE(j.PuedoAgregarPokemon(c2));
    ASSERT_TRUE(j.PuedoAgregarPokemon(c3));
    j.AgregarPokemon("Pikachu", c1);
    ASSERT_FALSE(j.PuedoAgregarPokemon(c1));
    ASSERT_FALSE(j.PuedoAgregarPokemon(c2));
    ASSERT_TRUE(j.PuedoAgregarPokemon(c3));
}

TEST_F(JuegoTest, colaEspera) {
    Juego j(m);
    Jugador e1 = j.AgregarJugador();
    Jugador e2 = j.AgregarJugador();
    Jugador e3 = j.AgregarJugador();

    j.Conectarse(e1, c1);
    j.Conectarse(e2, c1);
    j.Conectarse(e3, c1);

    j.AgregarPokemon("Pikachu", c1);

    aed2::Conj<Jugador> jugadores;
    jugadores.AgregarRapido(e1);
    jugadores.AgregarRapido(e2);
    jugadores.AgregarRapido(e3);
    ASSERT_EQ(j.EntrenadoresPosibles(jugadores, c1), jugadores);

    for(int i = 0; i < 10; ++i) {
        if(j.Posicion(e3) == c2) {
            j.Moverse(e3, c4);
        } else {
            j.Moverse(e3, c2);
        }
    }
    ASSERT_FALSE(j.HayPokemonCercano(c1));

    j.Moverse(e1, c4);
    j.Moverse(e2, c4);
    j.Moverse(e3, c4);
    j.AgregarPokemon("Pikachu", c1);
    ASSERT_TRUE(j.EntrenadoresPosibles(jugadores, c1).EsVacio());
}

// --------- TESTS DEL ITERADOR ---------

TEST_F(JuegoTest, jugadores) {
    Juego j(m);
    j.AgregarJugador();
    j.AgregarJugador();
    j.AgregarJugador();

    itJug = j.Jugadores();
    ASSERT_TRUE(itJug.HayMas());
    for(aed2::Nat i = 0; i < 3; ++i) {
        ASSERT_EQ(itJug.Actual(), i);
        itJug.Avanzar();
    }
    ASSERT_FALSE(itJug.HayMas());
}

TEST_F(JuegoTest, jugadoresVacio) {
    Juego j(m);
    itJug = j.Jugadores();
    ASSERT_FALSE(itJug.HayMas());
}

TEST_F(JuegoTest, expulsados) {
    Juego j(m);
    Jugador e1 = j.AgregarJugador();
    Jugador e2 = j.AgregarJugador();
    Jugador e3 = j.AgregarJugador();

    j.Conectarse(e2, c1);
    expulsar(j, e2);

    Juego::itJugadores it = j.Expulsados();
    ASSERT_TRUE(it.HayMas());
    ASSERT_EQ(it.Actual(), e2);
    it.Avanzar();
    ASSERT_FALSE(it.HayMas());

    itJug = j.Jugadores();
    ASSERT_TRUE(itJug.HayMas());
    ASSERT_EQ(itJug.Actual(), e1);
    itJug.Avanzar();
    ASSERT_TRUE(itJug.HayMas());
    ASSERT_EQ(itJug.Actual(), e3);
    itJug.Avanzar();
    ASSERT_FALSE(itJug.HayMas());

    expulsar(j, e3);it = j.Expulsados();
    ASSERT_TRUE(it.HayMas());
    ASSERT_EQ(it.Actual(), e2);
    it.Avanzar();
    ASSERT_TRUE(it.HayMas());
    ASSERT_EQ(it.Actual(), e3);
    it.Avanzar();
    ASSERT_FALSE(it.HayMas());

    itJug = j.Jugadores();
    ASSERT_TRUE(itJug.HayMas());
    ASSERT_EQ(itJug.Actual(), e1);
    itJug.Avanzar();
    ASSERT_FALSE(itJug.HayMas());
}