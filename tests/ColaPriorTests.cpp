#include "gtest/gtest.h"
#include "../TiposJuego.h"
#include "../ColaPrior.h"
#include "../aed2/Conj.h"
#include "../TuplaOrd.h"

// --------- FIXTURES ---------

class ColaPriorTest : public ::testing::Test {
protected:
    ColaPriorTest() : tup1(1,2), tup2(2, 2), tup3(3, 1), tup4(4,4), tup5(5,0) {}

    virtual void SetUp() {
        j1 = 1;
        j2 = 2;
        j3 = 3;
        j4 = 4;
        j5 = 5;

        js.AgregarRapido(j5);
        js.AgregarRapido(j4);
        js.AgregarRapido(j3);
        js.AgregarRapido(j2);
        js.AgregarRapido(j1);

    }

    Jugador j1;
    Jugador j2;
    Jugador j3;
    Jugador j4;
    Jugador j5;
    aed2::Conj<Jugador> js;

    ColaPrior<Jugador> cola1;
    ColaPrior<Jugador> cola2;

    TuplaOrd<Jugador, aed2::Nat> tup1;
    TuplaOrd<Jugador, aed2::Nat> tup2;
    TuplaOrd<Jugador, aed2::Nat> tup3;
    TuplaOrd<Jugador, aed2::Nat> tup4;
    TuplaOrd<Jugador, aed2::Nat> tup5;

    ColaPrior<TuplaOrd<Jugador, aed2::Nat> > colaTup;

    ColaPrior<Jugador>::const_Iterador it;
};

// --------- TESTS DE LA COLA ---------

TEST_F(ColaPriorTest, vacia) {
    ASSERT_TRUE(cola1.Vacia());
}

TEST_F(ColaPriorTest, proximo) {
    cola1.Encolar(j4);
    ASSERT_EQ(j4, cola1.Proximo());
    cola1.Encolar(j1);
    ASSERT_EQ(j1, cola1.Proximo());
    cola1.Encolar(j2);
    ASSERT_EQ(j1, cola1.Proximo());
    cola1.Desencolar();
    ASSERT_EQ(j2, cola1.Proximo());
}

TEST_F(ColaPriorTest, borrar) {
    cola1.Encolar(j4);
    cola1.Encolar(j1);
    ASSERT_EQ(j1, cola1.Proximo());
    cola1.Encolar(j2);
    cola1.Borrar(j4);
    cola1.Desencolar();
    ASSERT_EQ(j2, cola1.Proximo());
    cola1.Desencolar();
    ASSERT_TRUE(cola1.Vacia());
}

TEST_F(ColaPriorTest, elementos) {
    cola1.Encolar(j1);
    cola1.Encolar(j2);
    cola1.Encolar(j3);
    cola1.Encolar(j4);
    cola1.Encolar(j5);

    aed2::Conj<Jugador>::const_Iterador itJs;
    for(itJs = js.CrearIt(); itJs.HaySiguiente(); itJs.Avanzar()) {
        ASSERT_EQ(itJs.Siguiente(), cola1.Proximo());
        cola1.Desencolar();
    }
}

TEST_F(ColaPriorTest, igualdad) {
    cola1.Encolar(j1);
    cola1.Encolar(j2);
    cola1.Encolar(j3);
    cola1.Encolar(j4);
    cola1.Encolar(j5);
    cola2.Encolar(j1);
    cola2.Encolar(j2);
    cola2.Encolar(j3);
    cola2.Encolar(j4);
    ASSERT_NE(cola1, cola2);
    cola2.Encolar(j5);
    ASSERT_EQ(cola1, cola2);
}

TEST_F(ColaPriorTest, tuplas) {
    colaTup.Encolar(tup1);
    colaTup.Encolar(tup2);
    colaTup.Encolar(tup3);
    colaTup.Encolar(tup4);
    colaTup.Encolar(tup5);
    ASSERT_EQ(tup5, colaTup.Proximo());
    colaTup.Desencolar();
    ASSERT_EQ(tup3, colaTup.Proximo());
    colaTup.Desencolar();
    ASSERT_EQ(tup1, colaTup.Proximo());
    colaTup.Desencolar();
    ASSERT_EQ(tup2, colaTup.Proximo());
    colaTup.Desencolar();
    ASSERT_EQ(tup4, colaTup.Proximo());
}

// --------- TESTS DEL ITERADOR ---------

TEST_F(ColaPriorTest, itVacio) {
    it = cola1.CrearIt();
    ASSERT_FALSE(it.HayMas());
}

TEST_F(ColaPriorTest, itHayMas) {
    cola1.Encolar(j1);
    cola1.Encolar(j2);

    it = cola1.CrearIt();
    ASSERT_TRUE(it.HayMas());
    it.Avanzar();
    ASSERT_TRUE(it.HayMas());
    it.Avanzar();
    ASSERT_FALSE(it.HayMas());
}


TEST_F(ColaPriorTest, itActual) {
    cola1.Encolar(j1);
    cola1.Encolar(j2);
    cola1.Encolar(j3);

    // Por como se balancea y se itera, se asume este orden de elementos
    it = cola1.CrearIt();
    ASSERT_EQ(j2, it.Actual());
    it.Avanzar();
    ASSERT_EQ(j1, it.Actual());
    it.Avanzar();
    ASSERT_EQ(j3, it.Actual());
}

TEST_F(ColaPriorTest, itElems) {
    cola1.Encolar(j1);
    cola1.Encolar(j2);
    cola1.Encolar(j3);
    cola1.Encolar(j4);
    cola1.Encolar(j5);

    aed2::Conj<Jugador> conjAux;
    for(it = cola1.CrearIt(); it.HayMas(); it.Avanzar()) {
        conjAux.AgregarRapido(it.Actual());
    }
    ASSERT_EQ(js, conjAux);
}