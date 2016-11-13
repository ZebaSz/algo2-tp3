#ifndef CONJ_ORD_H
#define CONJ_ORD_H

#include "../aed2/TiposBasicos.h"
#include "../aed2/Lista.h"
#include <iostream>

template<typename T>
class ConjuntoOrd {
friend class const_Iterador;
public:
    ConjuntoOrd();

    ~ConjuntoOrd();

    void Agregar(const T& elem);

    bool Pertenece(const T& elem) const;

    bool Vacio() const;

    void Borrar(const T& elem);

    const T& Minimo() const;

    class const_Iterador {
    friend class ConjuntoOrd;

    public:
        const_Iterador();

        bool HayMas() const;

        const T& Actual() const;

        void Avanzar();

    private:
        const_Iterador(const ConjuntoOrd*);

        aed2::Lista<typename ConjuntoOrd<T>::Nodo*> _pila;
        const ConjuntoOrd* _conj;
    };

    const_Iterador CrearIt() const;

    template<typename S>
    friend bool operator==(const ConjuntoOrd<S>&, const ConjuntoOrd<S>&);

    template<typename S>
    friend bool operator!=(const ConjuntoOrd<S>&, const ConjuntoOrd<S>&);

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

    aed2::Nat CantClaves() const;

    Nodo* _raiz;
};

template <typename T>
ConjuntoOrd<T>::ConjuntoOrd()
    : _raiz(NULL){
}

template <typename T>
ConjuntoOrd<T>::~ConjuntoOrd(){
    delete _raiz;
}

// TODO: estas operaciones corresponden a ABBs, no AVLs; refactorizar con rotaciones, etc.

template <typename T>
void ConjuntoOrd<T>::Agregar(const T& elem) {
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
}

template <typename T>
bool ConjuntoOrd<T>::Pertenece(const T& elem) const{
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
bool ConjuntoOrd<T>::Vacio() const{
    return _raiz == NULL;
}

template <typename T>
void ConjuntoOrd<T>::Borrar(const T& elem) {
    if (_raiz != NULL) {
        // borrarElem(_raiz, elem); //TODO
    }
}

template <typename T>
const T& ConjuntoOrd<T>::Minimo() const {
    Nodo* pos = _raiz;
    while (pos->izq != NULL){
        pos = pos->izq;
    }
    return pos->valor;
}

template <typename T>
aed2::Nat ConjuntoOrd<T>::CantClaves() const {
    aed2::Nat cant(0);
    for(const_Iterador it(this); it.HayMas(); it.Avanzar()) {
        ++cant;
    }
    return cant;
}

template <typename T>
typename ConjuntoOrd<T>::const_Iterador ConjuntoOrd<T>::CrearIt() const {
    return ConjuntoOrd::const_Iterador(this);
}

template <typename T>
bool operator==(const ConjuntoOrd<T>& c1, const ConjuntoOrd<T>& c2) {
    if(c1.CantClaves() != c2.CantClaves()) {
        return false;
    }
    typename ConjuntoOrd<T>::const_Iterador it = c1.CrearIt();
    while(it.HayMas()) {
        if(!c2.Pertenece(it.Actual())) {
            return false;
        }
        it.Avanzar();
    }
    return true;
}

template <typename T>
bool operator!=(const ConjuntoOrd<T>& c1, const ConjuntoOrd<T>& c2) {
    return not (c1 == c2);
}

// ITERADOR

template <typename T>
ConjuntoOrd<T>::const_Iterador::const_Iterador() : _conj(NULL) {
}

template <typename T>
ConjuntoOrd<T>::const_Iterador::const_Iterador(const ConjuntoOrd* conj)
        : _pila(), _conj(conj) {
    if(_conj->_raiz != NULL) {
        _pila.AgregarAdelante(_conj->_raiz);
    }
}

template <typename T>
bool ConjuntoOrd<T>::const_Iterador::HayMas() const {
    return !_pila.EsVacia();
}

template <typename T>
const T& ConjuntoOrd<T>::const_Iterador::Actual() const {
    return _pila.Primero()->valor;
}

template <typename T>
void ConjuntoOrd<T>::const_Iterador::Avanzar() {
    Nodo* tope = _pila.Primero();
    if(tope->izq != NULL) {
        _pila.AgregarAdelante(tope->izq);
    } else {
        _pila.Fin();
        while(!_pila.EsVacia() && tope->der == NULL) {
            tope = _pila.Primero();
            _pila.Fin();
        }
        if(tope->der != NULL) {
            _pila.AgregarAdelante(tope->der);
        }
    }
}

#endif