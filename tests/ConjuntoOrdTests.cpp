#include "gtest/gtest.h"
#include "../TiposJuego.h"
#include "../modulos/ConjuntoOrd.h"
#include "../aed2/Conj.h"

// --------- FIXTURES ---------

class ConjuntoOrdTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        j1 = 1;
        j2 = 2;
        j3 = 3;
        j4 = 4;
        j5 = 5;

        js.AgregarRapido(j1);
        js.AgregarRapido(j2);
        js.AgregarRapido(j3);
        js.AgregarRapido(j4);
        js.AgregarRapido(j5);
    }

    Jugador j1;
    Jugador j2;
    Jugador j3;
    Jugador j4;
    Jugador j5;
    aed2::Conj<Jugador> js;

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

TEST_F(ConjuntoOrdTest, elementos) {
    conj1.Agregar(j1);
    conj1.Agregar(j2);
    conj1.Agregar(j3);
    conj1.Agregar(j4);
    conj1.Agregar(j5);

    aed2::Conj<Jugador>::const_Iterador itJs;
    for(itJs = js.CrearIt(); itJs.HaySiguiente(); itJs.Avanzar()) {
        ASSERT_TRUE(conj1.Pertenece(itJs.Siguiente()));
    }
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

// --------- TESTS DEL ITERADOR ---------


TEST_F(ConjuntoOrdTest, itVacio) {
    it = conj1.CrearIt();
    ASSERT_FALSE(it.HayMas());
}

TEST_F(ConjuntoOrdTest, itElems) {
    conj1.Agregar(j1);
    conj1.Agregar(j2);
    conj1.Agregar(j3);
    conj1.Agregar(j4);
    conj1.Agregar(j5);

    aed2::Conj<Jugador> conjAux;
    for(it = conj1.CrearIt(); it.HayMas(); it.Avanzar()) {
        conjAux.AgregarRapido(it.Actual());
    }
    ASSERT_EQ(js, conjAux);
}

// --------- TESTS CON OPCIONES DE DEBUG ---------

TEST_F(ConjuntoOrdTest, factBal) {
    conj1.Agregar(j1);
    conj1.Agregar(j2);
    conj1.Agregar(j3);
    conj1.Agregar(j4);
    conj1.Agregar(j5);

    for(it = conj1.CrearIt(); it.HayMas(); it.Avanzar()) {
        aed2::Nat alturaIzq = it._conj->Altura(it._pila.Primero()->izq);
        aed2::Nat alturaDer = it._conj->Altura(it._pila.Primero()->der);
        aed2::Nat factorBal = alturaDer > alturaIzq ? alturaDer - alturaIzq : alturaIzq - alturaDer;
        ASSERT_LE(factorBal, aed2::Nat(1));
    }
}