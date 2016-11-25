#ifndef CONJ_ORD_H
#define CONJ_ORD_H

#include "../aed2/TiposBasicos.h"
#include "../aed2/Lista.h"
#include <iostream>

template<typename T>
class ConjuntoOrd {
public:
    ConjuntoOrd();

    ~ConjuntoOrd();

    void Agregar(const T& elem);

    bool Pertenece(const T& elem) const;

    bool Vacio() const;

    void Borrar(const T& elem);

    const T& Minimo() const;

    void Vaciar();

    class const_Iterador {
    public:
        const_Iterador();

        bool HayMas() const;

        const T& Actual() const;

        void Avanzar();

        friend class ConjuntoOrd;

        // TESTS DE ESTR INTERNA
        friend class ConjuntoOrdTest_factBal_Test;

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

    template<typename S>
    friend std::ostream& operator<<(std::ostream&, const ConjuntoOrd<S>&);

    // TESTS DE ESTR INTERNA
    friend class ConjuntoOrdTest_factBal_Test;

private:
    struct Nodo {
        Nodo(const T& v) : valor(v), altura(1), izq(NULL), der(NULL) {};

        Nodo(const Nodo& otro) : valor(otro.valor), altura(otro.altura), izq(NULL), der(NULL) {
            if(otro.izq != NULL) {
                izq = new Nodo(*otro.izq);
            }
            if(otro.der != NULL) {
                der = new Nodo(*otro.der);
            }
        }

        ~Nodo() {
            if(this->izq != NULL) delete this->izq;
            if(this->der != NULL) delete this->der;
        }

        T valor;
        aed2::Nat altura;
        Nodo* izq;
        Nodo* der;
    };

    aed2::Nat CantElems() const;

    Nodo* InsertarNodo(const T& elem, Nodo* p);

    Nodo* BorrarNodo(const T& elem, Nodo* p);

    Nodo* BuscarMinimo(Nodo* p);

    Nodo* RemoverMinimo(Nodo* p);

    Nodo* Balancear(Nodo* p);

    aed2::Nat Altura(const Nodo* p) const;

    Nodo* rotarIzq(Nodo* p);

    Nodo* rotarDer(Nodo* p);

    void ArreglarAlto(Nodo* p);

    Nodo* _raiz;

    void Mostrar(std::ostream&, const Nodo*) const;
};

template <typename T>
ConjuntoOrd<T>::ConjuntoOrd()
    : _raiz(NULL){
}

template <typename T>
ConjuntoOrd<T>::~ConjuntoOrd(){
    delete _raiz;
}

template <typename T>
void ConjuntoOrd<T>::Agregar(const T& elem) {
    if(!Pertenece(elem)){
        _raiz = InsertarNodo(elem, _raiz);
    }
}

template <typename T>
bool ConjuntoOrd<T>::Pertenece(const T& elem) const{
    Nodo* pos = _raiz;
    while (pos != NULL && pos->valor != elem){
        if (elem < pos->valor) {
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
    if (_raiz != NULL){
        _raiz = BorrarNodo(elem, _raiz);
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
void ConjuntoOrd<T>::Vaciar() {
    delete _raiz;
    _raiz = NULL;
}

template <typename T>
aed2::Nat ConjuntoOrd<T>::CantElems() const {
    aed2::Nat cant(0);
    for(const_Iterador it(this); it.HayMas(); it.Avanzar()) {
        ++cant;
    }
    return cant;
}

template <typename T>
typename ConjuntoOrd<T>::Nodo* ConjuntoOrd<T>::Balancear(Nodo* p){
    ArreglarAlto(p);
    aed2::Nat alturaIzq = Altura(p->izq);
    aed2::Nat alturaDer = Altura(p->der);
    if (alturaDer > alturaIzq && (alturaDer - alturaIzq == 2)){
        if (Altura(p->der->izq) > Altura(p->der->der)){
            p->der = rotarDer(p->der);
        }
        return rotarIzq(p);
    } else if (alturaIzq > alturaDer && (alturaIzq - alturaDer == 2)){
        if (Altura(p->izq->der) > Altura(p->izq->izq)){
            p->izq = rotarIzq(p->izq);
        }
        return rotarDer(p);
    } else {
        return p;
    }
}

template <typename T>
typename ConjuntoOrd<T>::Nodo* ConjuntoOrd<T>::InsertarNodo(const T& elem, Nodo* p){
    if (p == NULL){
        return (new Nodo(elem));
    } else if (elem < p->valor){
        p->izq = InsertarNodo(elem, p->izq);
    } else {
        p->der = InsertarNodo(elem, p->der);
    }
    return Balancear(p);
}

template <typename T>
aed2::Nat ConjuntoOrd<T>::Altura(const Nodo* p) const{
    if (p == NULL){
        return 0;
    } else {
        return p->altura;
    }
}

template <typename T>
typename ConjuntoOrd<T>::Nodo* ConjuntoOrd<T>::rotarIzq(Nodo* p){
    Nodo *aux = p->der;
    p->der = aux->izq;
    aux->izq = p;
    ArreglarAlto(p);
    ArreglarAlto(aux);
    return aux;
}

template <typename T>
typename ConjuntoOrd<T>::Nodo* ConjuntoOrd<T>::rotarDer(Nodo* p){
    Nodo *aux = p->izq;
    p->izq = aux->der;
    aux->der = p;
    ArreglarAlto(p);
    ArreglarAlto(aux);
    return aux;
}

template <typename T>
void ConjuntoOrd<T>::ArreglarAlto(Nodo* p){
    aed2::Nat alturaIzq = Altura(p->izq);
    aed2::Nat alturaDer = Altura(p->der);
    if (alturaIzq < alturaDer) {
        p->altura = alturaDer + 1;
    } else{
        p->altura = alturaIzq + 1;
    }
}

template <typename T>
typename ConjuntoOrd<T>::Nodo* ConjuntoOrd<T>::BorrarNodo(const T &elem, Nodo *p){
    if (p == NULL){
        return p;
    } else if (elem < p->valor){
        p->izq = BorrarNodo(elem, p->izq);
        return Balancear(p);
    } else if (p->valor < elem){
        p->der = BorrarNodo(elem, p->der);
        return Balancear(p);
    } else{
        Nodo *i = p->izq;
        Nodo *d = p->der;
        if (d == NULL){
            p->izq = NULL;
            delete p;
            return i;
        } else {
            Nodo *minimo = BuscarMinimo(d);
            minimo->der = RemoverMinimo(d);
            minimo->izq = i;
            p->izq = NULL;
            p->der = NULL;
            delete p;
            return Balancear(minimo);
        }
    }
}

template <typename T>
typename ConjuntoOrd<T>::Nodo* ConjuntoOrd<T>::BuscarMinimo(Nodo *p){
    if (p->izq == NULL){
        return p;
    } else {
        return BuscarMinimo(p->izq);
    }
}

template <typename T>
typename ConjuntoOrd<T>::Nodo* ConjuntoOrd<T>::RemoverMinimo(Nodo *p){
    if (p->izq == NULL){
        return p->der;
    } else {
        p->izq = RemoverMinimo(p->izq);
        return Balancear(p);
    }
}

template <typename T>
typename ConjuntoOrd<T>::const_Iterador ConjuntoOrd<T>::CrearIt() const {
    return ConjuntoOrd::const_Iterador(this);
}

template <typename T>
bool operator==(const ConjuntoOrd<T>& c1, const ConjuntoOrd<T>& c2) {
    if(c1.CantElems() != c2.CantElems()) {
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

template<class T>
std::ostream& operator<<(std::ostream& os, const ConjuntoOrd<T>& c) {
    os << '{';
    c.Mostrar(os, c._raiz);
    return os << '}';
}

template<class T>
void ConjuntoOrd<T>::Mostrar(std::ostream& os, const Nodo* nodo) const {
    if(nodo->izq != NULL) {
        Mostrar(os, nodo->izq);
        os << ',';
    }
    os << nodo->valor;
    if(nodo->der != NULL) {
        os << ',';
        Mostrar(os, nodo->der);
    }
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