/**
 * Archivo para poner los tests
 * Se pueden usar fixtures para reusar instancias de nuestras clases
 * en lugar de copiar y pegar por todos lados
 */
#include "gtest/gtest.h"
#include "Driver.h"

class CoordsTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        cc.Agregar(Coordenada(0,0));
        cc.Agregar(Coordenada(0,1));
        cc.Agregar(Coordenada(0,2));
        cc.Agregar(Coordenada(1,2));
        cc.Agregar(Coordenada(10,0));
        cc.Agregar(Coordenada(1,4));
    }

    aed2::Conj<Coordenada> cc;
};

TEST_F(CoordsTest, test_constructor_con_mapa) {
    Driver d(cc);
    ASSERT_EQ(d.mapa(), cc);
}

TEST(JuegoTest, test_agregar_jugadores){
    ASSERT_TRUE(false);
}

TEST(JuegoTest, test_agregar_pokemones){
    ASSERT_TRUE(false);
}