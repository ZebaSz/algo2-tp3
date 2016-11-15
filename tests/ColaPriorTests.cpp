#include "gtest/gtest.h"
#include "../TiposJuego.h"
#include "../modulos/ColaPrior.h"
#include "../aed2/Conj.h"

// --------- FIXTURES ---------

class ColaPriorTest : public ::testing::Test {
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
    aed2::Conj<Jugador> js;

    ColaPrior<Jugador> cola1;
    ColaPrior<Jugador> cola2;
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

/*TEST_F(ColaPriorTest, elementos) {
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

TEST_F(ColaPriorTest, igualdad) {
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


TEST_F(ColaPriorTest, itVacio) {
    it = conj1.CrearIt();
    ASSERT_FALSE(it.HayMas());
}

TEST_F(ConjuntoOrdTest, itHayMas) {
    conj1.Agregar(j1);
    conj1.Agregar(j2);

    it = conj1.CrearIt();
    ASSERT_TRUE(it.HayMas());
    it.Avanzar();
    ASSERT_TRUE(it.HayMas());
    it.Avanzar();
    ASSERT_FALSE(it.HayMas());
}


TEST_F(ColaPriorTest, itActual) {
    conj1.Agregar(j1);
    conj1.Agregar(j2);
    conj1.Agregar(j3);

    // Por como se balancea y se itera, se asume este orden de elementos
    it = conj1.CrearIt();
    ASSERT_EQ(j2, it.Actual());
    it.Avanzar();
    ASSERT_EQ(j1, it.Actual());
    it.Avanzar();
    ASSERT_EQ(j3, it.Actual());
}

TEST_F(ColaPriorTest, itElems) {
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
}*/