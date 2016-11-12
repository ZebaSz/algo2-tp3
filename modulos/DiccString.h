#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "../aed2/Conj.h"
#include <iostream>

template<typename T>
class DiccString {
public:
    DiccString();

    ~DiccString();

    void Definir(const aed2::String& clave, const T& significado);

    bool Definido(const aed2::String& clave) const;

    const T Obtener(const aed2::String& clave) const;

    T Obtener(const aed2::String& clave);

    void Borrar(const aed2::String& clave);

    const aed2::Conj<aed2::String>& Claves() const;

    struct Entrada {
        Entrada(const aed2::String& key, T value) : clave(key), valor(value) {}

        friend bool operator==(const Entrada& en1, const Entrada& en2) {
            return en1.clave == en2.clave && en1.valor == en2.valor;
        }

        friend bool operator!=(const Entrada& en1, const Entrada& en2) {
            return not (en1 == en2);
        }

        friend std::ostream& operator<<(std::ostream& os, const Entrada& en) {
            os << '<' << en.clave << ',' << en.valor << '>';
        }

        aed2::String clave;
        T valor;
    };

    class const_Iterador {
    friend class DiccString;

    public:
        const_Iterador() {}

        bool HaySiguiente() const;

        bool HayAnterior() const;

        const Entrada Siguiente() const;

        const Entrada Anterior() const;

        void Avanzar();

        void Retroceder();

    private:
        const_Iterador(const DiccString*);

        typename aed2::Conj<aed2::String>::const_Iterador _itClaves;
        const DiccString* _dic;
    };

    const_Iterador CrearIt() const;

    template<typename S>
    friend bool operator==(const DiccString<S>&, const DiccString<S>&);

    template<typename S>
    friend bool operator!=(const DiccString<S>&, const DiccString<S>&);

private:

    struct Nodo{
        Nodo() : valor(NULL) {
            for (int i = 0; i < 256; i++){
                hijos[i] = NULL;
            }
        }

        ~Nodo() {
            for(int i = 0; i < 256; ++i) {
                delete hijos[i];
            }
            delete valor;
        }

        Nodo* hijos[256];
        T* valor;
    };

    Nodo* _raiz;
    aed2::Conj<aed2::String> _claves;
};

template <typename T>
DiccString<T>::DiccString()
    : _raiz(new Nodo()), _claves(){
}

template <typename T>
DiccString<T>::~DiccString(){
    delete _raiz;
}

template <typename T>
void DiccString<T>::Definir(const aed2::String& clave, const T& significado){
    Nodo* entrada = _raiz;
    for(size_t i = 0; i < clave.size(); ++i) {
        if(entrada->hijos[int(clave[i])] == NULL) {
            entrada->hijos[int(clave[i])] = new Nodo();
        }
        entrada = entrada->hijos[int(clave[i])];
    }
    if(entrada->valor == NULL) {
        _claves.AgregarRapido(clave);
    } else {
        delete entrada->valor;
    }
    entrada->valor = new T(significado);
}


template <typename T>
bool DiccString<T>::Definido(const aed2::String& clave) const{
    Nodo* entrada = _raiz;
    for(size_t i = 0; i < clave.size(); ++i) {
        if(entrada == NULL) {
            break;
        }
        entrada = entrada->hijos[int(clave[i])];
    }
    return entrada != NULL && entrada->valor != NULL;
}

template <typename T>
T DiccString<T>::Obtener(const aed2::String& clave) {
    Nodo* actual = _raiz;
    for(size_t i = 0; i < clave.size(); ++i) {
        actual = actual->hijos[int(clave[i])];
    }
    return *actual->valor;
}


template <typename T>
const T DiccString<T>::Obtener(const aed2::String& clave) const {
    Nodo* actual = _raiz;
    for(size_t i = 0; i < clave.size(); ++i) {
        actual = actual->hijos[int(clave[i])];
    }
    return *actual->valor;
}


template <typename T>
void DiccString<T>::Borrar(const aed2::String& clave) {
    Nodo* actual = _raiz;
    for(size_t i = 0; i < clave.size(); ++i) {
        actual = actual->hijos[int(clave[i])];
    }
    delete actual->valor;
    actual->valor = NULL;
    _claves.Eliminar(clave);
}


template <typename T>
const aed2::Conj<aed2::String>& DiccString<T>::Claves() const{
    return _claves;
}

template <typename T>
typename DiccString<T>::const_Iterador DiccString<T>::CrearIt() const {
    return DiccString::const_Iterador(this);
}

template <typename T>
bool operator==(const DiccString<T>& d1, const DiccString<T>& d2) {
    if(!(d1.Claves() == d2.Claves())) {
        return false;
    }
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
bool operator!=(const DiccString<T>& d1, const DiccString<T>& d2) {
    return not (d1 == d2);
}

// ITERADOR


template <typename T>
DiccString<T>::const_Iterador::const_Iterador(const DiccString* dicc)
        : _itClaves(dicc->_claves.CrearIt()), _dic(dicc) {
}

template <typename T>
bool DiccString<T>::const_Iterador::HaySiguiente() const {
    return _itClaves.HaySiguiente();
}

template <typename T>
bool DiccString<T>::const_Iterador::HayAnterior() const {
    return _itClaves.HayAnterior();
}

template <typename T>
const typename DiccString<T>::Entrada DiccString<T>::const_Iterador::Siguiente() const {
    return Entrada(_itClaves.Siguiente(), _dic->Obtener(_itClaves.Siguiente()));
}

template <typename T>
const typename DiccString<T>::Entrada DiccString<T>::const_Iterador::Anterior() const {
    return Entrada(_itClaves.Anterior(), _dic->Obtener(_itClaves.Anterior()));
}

template <typename T>
void DiccString<T>::const_Iterador::Avanzar() {
    _itClaves.Avanzar();
}

template <typename T>
void DiccString<T>::const_Iterador::Retroceder() {
    _itClaves.Retroceder();
}

#endif
