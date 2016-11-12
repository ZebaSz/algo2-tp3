#ifndef CONJ_ORD_H
#define CONJ_ORD_H

#include <iostream>

template<typename T>
class ConjOrd {
public:
    ConjOrd();

    ~ConjOrd();

    void Agregar(const T& elem);

    bool Pertenece(const T& elem) const;

    bool Vacio() const;

    void Borrar(const T& elem);

    const T Minimo() const;

    T Minimo() const;

    class const_Iterador {
        friend class ConjOrd;

    public:
        bool HayMas() const;

        const T Actual() const;

        void Avanzar();

    private:
        const_Iterador(const ConjOrd*);

        typename aed2::Conj<T>::const_Iterador _itElem;
        const ConjOrd* _conj;
    };

    const_Iterador CrearIt() const;

    template<typename S>
    friend bool operator==(const ConjOrd<S>&, const ConjOrd<S>&);

    template<typename S>
    friend bool operator!=(const ConjOrd<S>&, const ConjOrd<S>&);

private:
    struct Nodo {
        Nodo(const T& v) : valor(v), izq(NULL), der(NULL) {};

        ~Nodo() {
            if(this->izq != NULL) delete this->izq;
            if(this->der != NULL) delete this->der;
        }

        T valor;
        Nodo* izq;
        Nodo* der;
    };

    Nodo* _raiz;
};

//TODO comentario de roni:
// lo hice siguiendo la idea que uso seba en diccstring, donde el nodo se encarga de borrar a sus hijos, pero capaz flashie. Lo dejo porsilasdu

template <typename T>
ConjOrd<T>::ConjOrd()
    : _raiz(new Nodo()){
}

template <typename T>
ConjOrd<T>::~ConjOrd(){
    delete _raiz;
}

template <typename T>
void ConjOrd<T>::Agregar(const T& elem) {
    Nodo *pos = _raiz;
    Nodo *sigPos = _raiz;
    if (pos == NULL) {
        _raiz = new Nodo(elem);
    } else {
        while (sigPos != NULL) {
            if (pos->valor > elem) {
                pos = sigPos;
                sigPos = sigPos->izq;
            } else if (pos->valor < elem) {
                pos = sigPos;
                sigPos = sigPos->der;
            }
        }
        Nodo* nodoElem = new Nodo(elem);
        if (pos->valor > elem) {
            pos->izq = nodoElem;
        } else if (pos->valor < elem) {
            pos->der = nodoElem;
        }
    }
}//TODO no habia un Pre que prohiba el ingreso de un elemento existente, entonces porlasdudas chequee que no se agregue de nuevo

template <typename T>
bool ConjOrd<T>::Pertenece(const T& elem){
    Nodo* pos = _raiz;
    while (pos != NULL && pos->valor != elem){
        if (pos->valor > elem) {
            pos = pos->izq;
        } else if (pos->valor < elem){
            pos = pos->der;
        }
    }
    return (pos != NULL && pos->valor == elem);
}

template <typename T>
bool ConjOrd<T>::Vacio(){
    return _raiz == NULL;
}

template <typename T>
void ConjOrd<T>::Borrar(const T& elem) {
    if (_raiz != NULL) {
        borrarElem(_raiz, elem); //TODO
    }
}

template <typename T>
const T ConjOrd<T>::Minimo(const T& elem){
    Nodo* pos = _raiz;
    while (pos->izq != NULL){
        pos = pos->izq;
    }
    return pos->valor;
}

template <typename T>
T ConjOrd<T>::Minimo()(const T& elem){
    Nodo* pos = _raiz;
    while (pos->izq != NULL){
        pos = pos->izq;
    }
    return pos->valor;
}

typename ConjOrd<T>::const_Iterador ConjOrd<T>::CrearIt() const {
    return ConjOrd::const_Iterador(this);
}

template <typename T>
bool operator==(const ConjOrd<T>& c1, const ConjOrd<T>& c2) {
    //TODO
    aed2::Conj<aed2::String>::const_Iterador itClaves = d1.Claves().CrearIt();
    while(itClaves.HaySiguiente()) {
        if(d1.Obtener(itClaves.Siguiente()) != d2.Obtener(itClaves.Siguiente())) {
            return false;
        }
        itClaves.Avanzar();
    }
    return true;
}

template <typename T>
bool operator!=(const DiccString<T>& c1, const DiccString<T>& c2) {
    return not (c1 == c2);
}

// ITERADOR