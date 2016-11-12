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

    Mapa m;
    Coordenada c1;
    Coordenada c2;
    Coordenada c3;
    aed2::Conj<Coordenada> cc;
};

// --------- TESTS ---------

TEST_F(MapaTest, coordenadasCorrectas) {
    aed2::Conj<Coordenada>::const_Iterador it;
    for(it = cc.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        m.AgregarCoor(it.Siguiente());
    }
    ASSERT_EQ(m.Coordenadas(), cc);
}

TEST_F(MapaTest, conexionesCorrectas) {
    aed2::Conj<Coordenada>::const_Iterador it;
    for(it = cc.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        m.AgregarCoor(it.Siguiente());
    }
    ASSERT_TRUE(m.HayCamino(c1, c2));
    ASSERT_FALSE(m.HayCamino(c1, c3));
}