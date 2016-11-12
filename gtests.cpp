/**
 * Archivo para poner los tests
 * Se pueden usar fixtures para reusar instancias de nuestras clases
 * en lugar de copiar y pegar por todos lados
 */
#include "gtest/gtest.h"
#include "Driver.h"

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

class JuegoTest : public MapaTest {
protected:
    virtual void SetUp() {
        MapaTest::SetUp();
        Conj<Coordenada>::const_Iterador it;
        for(it = cc.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
            m.AgregarCoor(it.Siguiente());
        }
    }
};

class DriverTest : public MapaTest {
};

// --------- TESTS DEL MAPA ---------

TEST_F(MapaTest, coordenadasCorrectas) {
    Conj<Coordenada>::const_Iterador it;
    for(it = cc.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        m.AgregarCoor(it.Siguiente());
    }
    ASSERT_EQ(m.Coordenadas(), cc);
}

TEST_F(MapaTest, conexionesCorrectas) {
    Conj<Coordenada>::const_Iterador it;
    for(it = cc.CrearIt(); it.HaySiguiente(); it.Avanzar()) {
        m.AgregarCoor(it.Siguiente());
    }
    ASSERT_TRUE(m.HayCamino(c1, c2));
    ASSERT_FALSE(m.HayCamino(c1, c3));
}

// --------- TESTS DEL JUEGO ---------

TEST_F(JuegoTest, coordenadasMapa) {
    Juego j(m);
    ASSERT_EQ(j.ObtenerMapa().Coordenadas(), m.Coordenadas());
}

TEST_F(JuegoTest, agregarJugadores) {
    //ASSERT_TRUE(false);
}

TEST_F(JuegoTest, agregarPokemones){
    //ASSERT_TRUE(false);
}

// --------- TESTS DEL DRIVER ---------

TEST_F(DriverTest, constructorConMapa) {
    Driver d(cc);
    ASSERT_EQ(d.mapa(), cc);
}