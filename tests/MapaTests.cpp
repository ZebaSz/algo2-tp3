#include "gtest/gtest.h"
#include "../aed2/Conj.h"
#include "../modulos/Mapa.h"

// --------- FIXTURES ---------

class MapaTest : public ::testing::Test {
public:
    MapaTest() : c1(0,0), c2(1,2), c3(10,0) {}
protected:
    virtual void SetUp() {
        cc.Agregar(c1);
        cc.Agregar(Coordenada(0,1));
        cc.Agregar(Coordenada(0,2));
        cc.Agregar(c2);
        cc.Agregar(c3);
        cc.Agregar(Coordenada(1,4));
    }

    void agregarConjCoords(Mapa& m, const aed2::Conj<Coordenada> cs) {
        aed2::Conj<Coordenada>::const_Iterador it;
        for(it = cc.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
            m.AgregarCoor(it.Siguiente());
        }
    }

    Mapa m1;
    Mapa m2;
    Coordenada c1;
    Coordenada c2;
    Coordenada c3;
    aed2::Conj<Coordenada> cc;
};

// --------- TESTS ---------

TEST_F(MapaTest, vacio) {
    ASSERT_EQ(m1.Alto(), aed2::Nat(0));
    ASSERT_EQ(m1.Ancho(), aed2::Nat(0));
    ASSERT_TRUE(m1.Coordenadas().EsVacio());
}

TEST_F(MapaTest, coordenadasCorrectas) {
    agregarConjCoords(m1, cc);
    ASSERT_EQ(m1.Coordenadas(), cc);
}

TEST_F(MapaTest, conexionesCorrectas) {
    agregarConjCoords(m1, cc);
    ASSERT_TRUE(m1.HayCamino(c1, c2));
    ASSERT_FALSE(m1.HayCamino(c1, c3));
}

TEST_F(MapaTest, igualdad) {
    agregarConjCoords(m1, cc);
    m2.AgregarCoor(c1);
    m2.AgregarCoor(Coordenada(0,1));
    m2.AgregarCoor(Coordenada(0,2));
    m2.AgregarCoor(c2);
    m2.AgregarCoor(c3);
    ASSERT_NE(m1, m2);
    m2.AgregarCoor(Coordenada(1,4));
    ASSERT_EQ(m1, m2);
}

// --------- TESTS DE ESTRUCTURA INTERNA ---------

TEST_F(MapaTest, altoAncho) {
    agregarConjCoords(m1, cc);
    ASSERT_EQ(m1.Alto(), m1._posiciones.Longitud());
    ASSERT_EQ(m1.Ancho(), m1._posiciones[1].Longitud());
}