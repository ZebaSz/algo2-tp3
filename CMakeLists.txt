cmake_minimum_required(VERSION 2.8)
project(algo2_tp3)

set(SOURCE_FILES
    aed2/Arreglo.h
    aed2/Conj.h
    aed2/ConjAcotado.cpp
    aed2/ConjAcotado.h
    aed2/Dicc.h
    aed2/Lista.h
    aed2/TiposBasicos.h
    aed2/Vector.h
    aed2.h
    Driver.cpp
    Driver.h
    TiposJuego.h
    modulos/Juego.cpp
    modulos/Juego.h
    modulos/Mapa.cpp
    modulos/Mapa.h
    modulos/DiccString.h
    modulos/ConjuntoOrd.h
    modulos/ColaPrior.h)

set(TEST_FILES
    tests/MapaTests.cpp
    tests/DiccStringTests.cpp
    tests/ConjuntoOrdTests.cpp
    tests/JuegoTests.cpp
    tests/DriverTests.cpp
    tests/ColaPriorTests.cpp)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Wno-variadic-macros")

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(correrTests ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(correrTests gtest gtest_main)