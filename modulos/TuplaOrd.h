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

    friend bool operator==(const TuplaOrd<T,S>& t1, const TuplaOrd<T,S>& t2) {
        return (t1.primer == t2.primer && t1.segun == t2.segun);
    }

    friend std::ostream& operator<< (std::ostream& os, const TuplaOrd<T,S>& t1) {
        os << '<' << t1.primer << ',' << t1.segun << '>';
        return os;
    }

    friend bool operator!=(const TuplaOrd<T,S>& t1, const TuplaOrd<T,S>& t2) {
        return not (t1 == t2);
    }

    friend bool operator<(const TuplaOrd<T,S>& t1, const TuplaOrd<T,S>& t2) {
        return  (t1.segun < t2.segun || (t1.segun == t2.segun && t1.primer < t2.primer));
    }

    T primer;
    S segun;
};
#endif