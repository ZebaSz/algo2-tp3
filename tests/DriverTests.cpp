#include "gtest/gtest.h"
#include "../Driver.h"

// --------- FIXTURES ---------

class DriverTest : public ::testing::Test {
public:
    DriverTest() : c1(0,0), c2(1,2), c3(10,0) {}
protected:
    virtual void SetUp() {
        cc.Agregar(c1);
        cc.Agregar(Coordenada(0,1));
        cc.Agregar(Coordenada(0,2));
        cc.Agregar(c2);
        cc.Agregar(c3);
        cc.Agregar(Coordenada(1,4));
    }

    Coordenada c1;
    Coordenada c2;
    Coordenada c3;
    aed2::Conj<Coordenada> cc;
};

// --------- TESTS ---------

TEST_F(DriverTest, constructorConMapa) {
    Driver d(cc);
    ASSERT_EQ(d.mapa(), cc);
}