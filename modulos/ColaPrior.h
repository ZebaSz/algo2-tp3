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

    typedef typename ConjuntoOrd<T>::const_Iterador const_Iterador;

    const_Iterador CrearIt() const;

	template<typename S>
	friend bool operator==(const ColaPrior<S>&, const ColaPrior<S>&);

	template<typename S>
	friend bool operator!=(const ColaPrior<S>&, const ColaPrior<S>&);

    template<typename S>
    friend std::ostream& operator<<(std::ostream&, const ColaPrior<S>&);

private:
	ConjuntoOrd<T> _conjElem;
	T* _menor;
};

template <typename T>
ColaPrior<T>::ColaPrior() : _menor(NULL) {
}

template <typename T>
ColaPrior<T>::~ColaPrior(){
    delete _menor;
}

template <typename T>
void ColaPrior<T>::Encolar(const T &elem){
	_conjElem.Agregar(elem);
	if(_menor == NULL) {
        _menor = new T(elem);
    } else if (*_menor > elem){
        delete _menor;
        _menor = new T(elem);
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
void ColaPrior<T>::Desencolar() {
	_conjElem.Borrar(*_menor);
    delete _menor;
    if (! _conjElem.Vacio()){
        _menor = new T(_conjElem.Minimo());
    } else {
        _menor = NULL;
    }
}

template <typename T>
void ColaPrior<T>::Borrar(const T &elem){
	_conjElem.Borrar(elem);
    if (*_menor == elem){
        delete _menor;
        if (! _conjElem.Vacio()){
            _menor = new T(_conjElem.Minimo());
        } else {
            _menor = NULL;
        }
    }
}

template <typename T>
typename ColaPrior<T>::const_Iterador ColaPrior<T>::CrearIt() const {
	return _conjElem.CrearIt();
}

template<typename T>
bool operator==(const ColaPrior<T>& c1, const ColaPrior<T>& c2) {
    return c1._conjElem == c2._conjElem;
}

template<typename T>
bool operator!=(const ColaPrior<T>& c1, const ColaPrior<T>& c2) {
    return not (c1 == c2);
}

template<typename T>
std::ostream &operator<<(std::ostream& os, const ColaPrior<T>& c) {
    return os << c._conjElem;
}


#endif