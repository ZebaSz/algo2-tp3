#include "gtest/gtest.h"
#include "../aed2/Conj.h"
#include "../modulos/Juego.h"

// --------- FIXTURES ---------

class JuegoTest : public ::testing::Test {
public:
    JuegoTest() : c1(0,0), c2(1,2), c3(10,0) {}
protected:
    virtual void SetUp() {
        cc.Agregar(c1);
        cc.Agregar(Coordenada(0,1));
        cc.Agregar(Coordenada(0,2));
        cc.Agregar(c2);
        cc.Agregar(c3);
        cc.Agregar(Coordenada(1,4));
        aed2::Conj<Coordenada>::const_Iterador it;
        for(it = cc.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
            m.AgregarCoor(it.Siguiente());
        }
    }

    void expulsar(Juego& j, const Jugador e) {
        while(j.Sanciones(e) < 5) {
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
    ASSERT_EQ(j.AgregarJugador(), aed2::Nat(0));
    j.Conectarse(aed2::Nat(0), c3);
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Posicion(aed2::Nat(0)), c3);
    ASSERT_EQ(j.Sanciones(aed2::Nat(0)), aed2::Nat(0));
    j.Moverse(aed2::Nat(0), c1);
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Posicion(aed2::Nat(0)), c1);
    ASSERT_EQ(j.Sanciones(aed2::Nat(0)), aed2::Nat(1));
    j.Moverse(aed2::Nat(0), c3);
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Posicion(aed2::Nat(0)), c3);
    ASSERT_EQ(j.Sanciones(aed2::Nat(0)), aed2::Nat(2));
    j.Moverse(aed2::Nat(0), c1);
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Posicion(aed2::Nat(0)), c1);
    ASSERT_EQ(j.Sanciones(aed2::Nat(0)), aed2::Nat(3));
    j.Moverse(aed2::Nat(0), c3);
    ASSERT_TRUE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Posicion(aed2::Nat(0)), c3);
    ASSERT_EQ(j.Sanciones(aed2::Nat(0)), aed2::Nat(4));
    j.Moverse(aed2::Nat(0), c1);
    ASSERT_FALSE(j.EstaConectado(aed2::Nat(0)));
    ASSERT_EQ(j.Sanciones(aed2::Nat(0)), aed2::Nat(5));
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