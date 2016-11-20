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
    ASSERT_EQ(j.AgregarJugador(), aed2::Nat(1));
    ASSERT_EQ(j.AgregarJugador(), aed2::Nat(2));
}

TEST_F(JuegoTest, agregarPokemones){
    //ASSERT_TRUE(false);
}

// --------- TESTS DEL ITERADOR ---------

TEST_F(JuegoTest, jugadores) {
    Juego j(m);
    j.AgregarJugador();
    j.AgregarJugador();
    j.AgregarJugador();

    itJug = j.jugadores();
    ASSERT_TRUE(itJug.HayMas());
    for(aed2::Nat i = 0; i < 3; ++i) {
        ASSERT_EQ(itJug.Actual(), i);
        itJug.Avanzar();
    }
    ASSERT_FALSE(itJug.HayMas());
}

TEST_F(JuegoTest, jugadoresVacio) {
    Juego j(m);
    itJug = j.jugadores();
    ASSERT_FALSE(itJug.HayMas());
}