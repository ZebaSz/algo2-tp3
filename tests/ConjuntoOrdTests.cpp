#include "gtest/gtest.h"
#include "../TiposJuego.h"
#include "../modulos/ConjuntoOrd.h"

// --------- FIXTURES ---------

class ConjuntoOrdTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        j1 = 1;
        j2 = 2;
        j3 = 3;
        j4 = 4;
        j5 = 5;
    }

    Jugador j1;
    Jugador j2;
    Jugador j3;
    Jugador j4;
    Jugador j5;
    ConjuntoOrd<Jugador> conj1;
    ConjuntoOrd<Jugador> conj2;

    ConjuntoOrd<Jugador>::const_Iterador it;
};

// --------- TESTS DEL CONJUNTO ---------

TEST_F(ConjuntoOrdTest, vacio) {
    ASSERT_TRUE(conj1.Vacio());
}

TEST_F(ConjuntoOrdTest, minimo) {
    conj1.Agregar(j4);
    ASSERT_EQ(j4, conj1.Minimo());
    conj1.Agregar(j1);
    ASSERT_EQ(j1, conj1.Minimo());
    conj1.Agregar(j2);
    ASSERT_EQ(j1, conj1.Minimo());
}

TEST_F(ConjuntoOrdTest, igualdad) {
    conj1.Agregar(j1);
    conj1.Agregar(j2);
    conj1.Agregar(j3);
    conj1.Agregar(j4);
    conj1.Agregar(j5);
    conj2.Agregar(j1);
    conj2.Agregar(j2);
    conj2.Agregar(j3);
    conj2.Agregar(j4);
    ASSERT_NE(conj1, conj2);
    conj2.Agregar(j5);
    ASSERT_EQ(conj1, conj2);
}

// --------- TESTS DEL ITERADOR ---------t