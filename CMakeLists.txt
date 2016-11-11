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
    TiposJuego.h Juego.cpp Juego.h)

add_subdirectory(lib/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(correrTests ${SOURCE_FILES} gtests.cpp)
target_link_libraries(correrTests gtest gtest_main)