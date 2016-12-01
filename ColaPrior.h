#ifndef COLA_PRIOR_H
#define COLA_PRIOR_H

#include "ConjuntoOrd.h"
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
	typename ConjuntoOrd<T>::const_Iterador _menor;
};

template <typename T>
ColaPrior<T>::ColaPrior() {
}

template <typename T>
ColaPrior<T>::~ColaPrior(){
}

template <typename T>
void ColaPrior<T>::Encolar(const T &elem){
	_conjElem.Agregar(elem);
	if(!_menor.HayMas() || elem < _menor.Actual()) {
        _menor = _conjElem.Minimo();
    }
}

template <typename T>
bool ColaPrior<T>::Vacia() const {
	return _conjElem.Vacio();
}

template <typename T>
const T& ColaPrior<T>::Proximo() const{
	return _menor.Actual();
}

template <typename T>
void ColaPrior<T>::Desencolar() {
    Borrar(_menor.Actual());
}

template <typename T>
void ColaPrior<T>::Borrar(const T &elem) {
    bool eraMinimo = _menor.Actual() == elem;
	_conjElem.Borrar(elem);
    if (eraMinimo){
        if (!_conjElem.Vacio()){
            _menor = _conjElem.Minimo();
        } else {
            _menor = _conjElem.CrearIt();
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