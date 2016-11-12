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

    Mapa m;
    Coordenada c1;
    Coordenada c2;
    Coordenada c3;
    aed2::Conj<Coordenada> cc;
};

// --------- TESTS ---------

TEST_F(MapaTest, vacio) {
    ASSERT_EQ(m.Alto(), 0);
    ASSERT_EQ(m.Ancho(), 0);
    ASSERT_TRUE(m.Coordenadas().EsVacio());
}

TEST_F(MapaTest, coordenadasCorrectas) {
    agregarConjCoords(m, cc);
    ASSERT_EQ(m.Coordenadas(), cc);
}

TEST_F(MapaTest, conexionesCorrectas) {
    agregarConjCoords(m, cc);
    ASSERT_TRUE(m.HayCamino(c1, c2));
    ASSERT_FALSE(m.HayCamino(c1, c3));
}

// --------- TESTS CON OPCIONES DE DEBUG ---------

#ifdef DEBUG
TEST_F(MapaTest, altoAncho) {
    agregarConjCoords(m, cc);
    ASSERT_EQ(m.Alto(), Posiciones(m).Longitud());
    ASSERT_EQ(m.Ancho(), Posiciones(m)[1].Longitud());
}

const aed2::Vector< aed2::Vector< Mapa::dataPos > >& Posiciones(const Mapa& m) {
    return m._posiciones;
}
#endif