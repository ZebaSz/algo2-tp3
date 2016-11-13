#include "gtest/gtest.h"
#include "../TiposJuego.h"
#include "../modulos/DiccString.h"

// --------- FIXTURES ---------

class DiccStringTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        pk1 = "Pikachu";
        pk2 = "Pichu";
        pk3 = "Carlos";
        pk4 = "Togepi";
        pk5 = "";

        pks.AgregarRapido(pk1);
        pks.AgregarRapido(pk2);
        pks.AgregarRapido(pk3);
        pks.AgregarRapido(pk4);
    }
    
    Pokemon pk1;
    Pokemon pk2;
    Pokemon pk3;
    Pokemon pk4;
    Pokemon pk5;
    aed2::Conj<Pokemon> pks;
    DiccString<aed2::Nat> dicc1;
    DiccString<aed2::Nat> dicc2;

    DiccString<aed2::Nat>::const_Iterador it;
};

// --------- TESTS DEL DICCIONARIO ---------

TEST_F(DiccStringTest, vacio) {
    ASSERT_TRUE(dicc1.Claves().EsVacio());
}


TEST_F(DiccStringTest, claves) {
    dicc1.Definir(pk1, 1);
    dicc1.Definir(pk2, 1);
    dicc1.Definir(pk3, 1);
    dicc1.Definir(pk4, 1);
    ASSERT_EQ(dicc1.Claves(), pks);
}

TEST_F(DiccStringTest, definido) {
    dicc1.Definir(pk1, 1);
    ASSERT_TRUE(dicc1.Definido(pk1));
    dicc1.Definir(pk2, 1);
    ASSERT_TRUE(dicc1.Definido(pk1));
    ASSERT_TRUE(dicc1.Definido(pk2));
    dicc1.Definir(pk1, 2);
    ASSERT_TRUE(dicc1.Definido(pk1));
    ASSERT_TRUE(dicc1.Definido(pk2));
}

TEST_F(DiccStringTest, borrar) {
    dicc1.Definir(pk1, 1);
    ASSERT_TRUE(dicc1.Definido(pk1));
    dicc1.Definir(pk2, 1);
    ASSERT_TRUE(dicc1.Definido(pk1));
    ASSERT_TRUE(dicc1.Definido(pk2));
    dicc1.Definir(pk1, 2);
    ASSERT_TRUE(dicc1.Definido(pk1));
    ASSERT_TRUE(dicc1.Definido(pk2));
    dicc1.Borrar(pk1);
    ASSERT_FALSE(dicc1.Definido(pk1));
    ASSERT_TRUE(dicc1.Definido(pk2));
}

TEST_F(DiccStringTest, definiciones) {
    dicc1.Definir(pk1, 1);
    ASSERT_EQ(dicc1.Obtener(pk1), aed2::Nat(1));
    dicc1.Definir(pk2, 1);
    ASSERT_EQ(dicc1.Obtener(pk1), aed2::Nat(1));
    ASSERT_EQ(dicc1.Obtener(pk2), aed2::Nat(1));
    dicc1.Definir(pk1, 2);
    ASSERT_EQ(dicc1.Obtener(pk1), aed2::Nat(2));
    ASSERT_EQ(dicc1.Obtener(pk2), aed2::Nat(1));
}

TEST_F(DiccStringTest, definicionesConBorrado) {
    dicc1.Definir(pk1, 1);
    ASSERT_EQ(dicc1.Obtener(pk1), aed2::Nat(1));
    dicc1.Definir(pk2, 1);
    ASSERT_EQ(dicc1.Obtener(pk1), aed2::Nat(1));
    ASSERT_EQ(dicc1.Obtener(pk2), aed2::Nat(1));
    dicc1.Definir(pk1, 2);
    ASSERT_EQ(dicc1.Obtener(pk1), aed2::Nat(2));
    ASSERT_EQ(dicc1.Obtener(pk2), aed2::Nat(1));
    dicc1.Borrar(pk1);
    ASSERT_EQ(dicc1.Obtener(pk2), aed2::Nat(1));
}

TEST_F(DiccStringTest, claveVacia) {
    ASSERT_FALSE(dicc1.Definido(pk5));
    dicc1.Definir(pk5, 1);
    ASSERT_TRUE(dicc1.Definido(pk5));
    ASSERT_EQ(dicc1.Obtener(pk5), aed2::Nat(1));
    dicc1.Borrar(pk5);
    ASSERT_FALSE(dicc1.Definido(pk5));
}

TEST_F(DiccStringTest, igualdad) {
    dicc1.Definir(pk1, 1);
    dicc1.Definir(pk2, 2);
    dicc1.Definir(pk3, 3);
    dicc1.Definir(pk4, 4);
    dicc2.Definir(pk1, 1);
    dicc2.Definir(pk2, 2);
    dicc2.Definir(pk3, 3);
    ASSERT_NE(dicc1, dicc2);
    dicc2.Definir(pk4, 5);
    ASSERT_NE(dicc1, dicc2);
    dicc2.Definir(pk4, 4);
    ASSERT_EQ(dicc1, dicc2);
}

// --------- TESTS DEL ITERADOR ---------

TEST_F(DiccStringTest, itVacio) {
    it = dicc1.CrearIt();
    ASSERT_FALSE(it.HaySiguiente());
    ASSERT_FALSE(it.HayAnterior());
}

TEST_F(DiccStringTest, itAvanzarRetroceder) {
    dicc1.Definir(pk1, 1);
    dicc1.Definir(pk2, 2);

    it = dicc1.CrearIt();
    ASSERT_TRUE(it.HaySiguiente());
    ASSERT_FALSE(it.HayAnterior());

    it.Avanzar();
    ASSERT_TRUE(it.HaySiguiente());
    ASSERT_TRUE(it.HayAnterior());

    it.Avanzar();
    ASSERT_FALSE(it.HaySiguiente());
    ASSERT_TRUE(it.HayAnterior());
}

TEST_F(DiccStringTest, itSiguienteAnterior) {
    dicc1.Definir(pk1, 1);
    dicc1.Definir(pk2, 2);

    DiccString<aed2::Nat>::Entrada en1(pk1, 1);
    DiccString<aed2::Nat>::Entrada en2(pk2, 2);

    // El orden en que figuran para el iterador es inverso
    // porque se usa AgregarRapido al definir,
    // que agrega la clave al principio
    it = dicc1.CrearIt();
    ASSERT_EQ(it.Siguiente(), en2);

    it.Avanzar();
    ASSERT_EQ(it.Siguiente(), en1);
    ASSERT_EQ(it.Anterior(), en2);

    it.Avanzar();
    ASSERT_EQ(it.Anterior(), en1);
}

TEST_F(DiccStringTest, itClaves) {
    dicc1.Definir(pk1, 1);
    dicc1.Definir(pk2, 2);
    dicc1.Definir(pk3, 3);
    dicc1.Definir(pk4, 4);

    it = dicc1.CrearIt();

    aed2::Conj<Pokemon> clavesSig;
    while(it.HaySiguiente()) {
        clavesSig.AgregarRapido(it.Siguiente().clave);
        it.Avanzar();
    }
    ASSERT_EQ(pks, clavesSig);
    aed2::Conj<Pokemon> clavesAnt;
    while(it.HayAnterior()) {
        clavesAnt.AgregarRapido(it.Anterior().clave);
        it.Retroceder();
    }
    ASSERT_EQ(pks, clavesAnt);
}