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
void ConjOrd<T>::Agregar(const T& elem){
    Nodo* pos = _raiz;
    if (pos->valor == NULL){
        pos->valor = elem;
    }
}

template <typename T>
bool ConjOrd<T>::Pertenece(const T& elem) const{
}

template <typename T>
bool ConjOrd<T>::Vacio() const{
}

template <typename T>
void ConjOrd<T>::Borrar(const T& elem){
}

template <typename T>
const T ConjOrd<T>::Minimo() const{
}

template <typename T>
T ConjOrd<T>::Minimo() const{
}