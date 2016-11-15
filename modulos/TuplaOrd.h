#ifndef TUPLA_ORD_H
#define TUPLA_ORD_H

#include "../aed2/TiposBasicos.h"
#include <iostream>

template<typename T, typename S>
struct TuplaOrd{
    TuplaOrd(const T& prim, const S& seg) : primer(prim), segun(seg){};

    const T first() const{
        return primer;
    }

    const S second() const{
        return segun;
    }

    bool operator==(const TuplaOrd<T,S>& t1) {
        return (primer == t1.first() && t1.segun == t1.second());
    }

    bool operator!=(const TuplaOrd<T,S>& t1) {
        return (primer != t1.first() || segun != t1.second());
    }

    bool operator<(const TuplaOrd<T,S>& t1) {
        return  (segun < t1.second() || (segun == t1.second() && primer < t1.first()));
    }

    T primer;
    S segun;
};
#endif