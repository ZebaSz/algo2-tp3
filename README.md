# Algoritmos y Estructuras de Datos 2 - TP Implementación [![Build Status](https://travis-ci.com/ZebaSz/algo2-tp3.svg?token=RsVvgVhBTWzmo98qb3zh&branch=master)](https://travis-ci.com/ZebaSz/algo2-tp3)

## Trello

[Tablero de Trello del TP](https://trello.com/b/hXtL2sma/tp3-algo2)

## Cómo compilar el TP

El proyecto incluye un archivo `CMakeLists.txt` importable en CLion. Incluye un target `correrTests`, que ejecuta todos los tests del proyecto.

Si querés buildear a mano, también se provee el archivo `correrTests.sh`, que crea una carpeta `build`, compila todo ahí y corre los tests con Valgrind. Para limpiar, alcanza con borrar esa carpeta.

## Cómo agregar tests

En la carpeta `tests` hay archivos con tests escritos con Google Test. Se pueden hacer tests simples (con el macro `TEST`) o tests con fixtures, que permiten reusar variables (con el macro `TEST_F`).

Si se agrega un nuevo archivo de test, hay que agregarlo al `CMakeLists.txt`, bajo la variable `TEST_FILES`.

Hay muchos más features en GTest. [Acá](https://github.com/google/googletest/blob/master/googletest/docs/Primer.md) está la información básica de como usar Google Test.

### Tests de estructura interna

A veces hace falta testear algunas cosas de la estructura interna del TP. Para esto vamos a usar `friend class` aprovechando que cada test se considera una clase.

Primero, escribimos nuestro test en el archivo que corresponda. En este ejemplo, el test usa un fixture:

```
TEST_F(MiFixture, miTestInterno) {
    ... (mi test de estructura interna)
}
```

Luego, agregamos la clase de test como amiga de la clase testeada:

```
class miClase {
public:
    
    ... (mis métodos públicos, iteradores, etc.)

    friend class MiFixture_miTestInterno_Test;
    ... (otros tests de estructura interna)

private:

    ... (mis métodos privados y estructura interna)
}
```

El formato de la clase de test siempre es `casoDeTest_nombreDeTest_Test`.