#ifndef COLA_PRIOR_H
#define COLA_PRIOR_H

#include "../modulos/ConjuntoOrd.h"
#include <iostream>



template<typename T>
class ColaPrior {
public:
	ColaPrior();

	~ColaPrior();

	void Encolar(const T& elem);

	bool Vacia() const;

	const T& Proximo() const;

	void Desencolar();

	void Borrar(const T& elem);

    typename ConjuntoOrd<T>::const_Iterador CrearIt() const;

	template<typename S>
	friend bool operator==(const ColaPrior<S>&, const ColaPrior<S>&);

	template<typename S>
	friend bool operator!=(const ColaPrior<S>&, const ColaPrior<S>&);

private:
	ConjuntoOrd<T> _conjElem;
	T* _menor;
};

template <typename T>
ColaPrior<T>::ColaPrior() {
	ConjuntoOrd<T> newConj;
    _conjElem = newConj;
	_menor = NULL;
}

template <typename T>
ColaPrior<T>::~ColaPrior(){
    delete _menor;
	_menor = NULL;
}

template <typename T>
void ColaPrior<T>::Encolar(const T &elem){
	_conjElem.Agregar(elem);
	if(_menor == NULL) {
        T *newMenor = new T(elem);
        _menor = newMenor;
    } else if (*_menor > elem){
        T *newMenor = new T(elem);
        delete _menor;
        _menor = newMenor;
    }
}

template <typename T>
bool ColaPrior<T>::Vacia() const {
	return _conjElem.Vacio();
}

template <typename T>
const T& ColaPrior<T>::Proximo() const{
	return *_menor;
}

template <typename T>
void ColaPrior<T>::Desencolar(){
	_conjElem.Borrar(*_menor);
    delete _menor;
    if (! _conjElem.Vacio()){
        T* newMenor = new T(_conjElem.Minimo());
        _menor = newMenor;
    } else {
        _menor = NULL;
    }
}

template <typename T>
void ColaPrior<T>::Borrar(const T &elem){
	_conjElem.Borrar(elem);
    if (*_menor = elem){
        delete _menor;
        if (! _conjElem.Vacio()){
            T* newMenor = new T(_conjElem.Minimo());
            _menor = newMenor;
        } else {
            _menor = NULL;
        }
    }
}

template <typename T>
typename ConjuntoOrd<T>::const_Iterador ColaPrior<T>::CrearIt() const {
	return _conjElem.CrearIt();
}




#endif