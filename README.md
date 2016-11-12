# Algoritmos y Estructuras de Datos 2 - TP Implementación [![Build Status](https://travis-ci.com/ZebaSz/algo2-tp3.svg?token=RsVvgVhBTWzmo98qb3zh&branch=master)](https://travis-ci.com/ZebaSz/algo2-tp3)

## Trello

[Tablero de Trello del TP](https://trello.com/b/hXtL2sma/tp3-algo2)

## Cómo compilar el TP

El proyecto incluye un archivo `CMakeLists.txt` importable en CLion. Si querés buildear a mano podés correr los siguientes comandos:

```
mkdir build && cd build
cmake ..
make
```

Esto genera el archivo ejecutable `correrTests`. Se puede correr directamente o a través de Valgrind. El mismo ejecuta todos los tests del proyecto.

## Cómo agregar tests

En la carpeta `tests` hay archivos con tests escritos con Google Test. Se pueden hacer tests simples (con el macro `TEST`) o tests con fixtures, que permiten reusar variables (con el macro `TEST_F`).

Si se agrega un nuevo archivo de test, hay que agregarlo al `CMakeLists.txt`, bajo la variable `TEST_FILES`.

Hay muchos más features en GTest. [Acá](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md) está la información básica de como usar Google Test.