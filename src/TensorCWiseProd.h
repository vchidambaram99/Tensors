#ifndef TENSORCWISEPROD_H
#define TENSORCWISEPROD_H
#include "DimsException.h"
#include "TensorExpression.h"
#include "Traits.h"

template<typename T1, typename T2>
class TensorCWiseProd : public TensorExpression<TensorCWiseProd<T1,T2>>{
public:
    using datatype = typename Traits<TensorCWiseProd<T1,T2>>::datatype;
    const T1& a;
    const T2& b;
    TensorCWiseProd(const T1& u, const T2& v):a(u),b(v){
        if(!a.equalDims(b))throw DimsException(a.dims(),b.dims());
    }
    datatype operator[](std::size_t i) const { return a[i] * b[i]; }
    std::size_t size()                 const { return a.size();    }
    std::vector<std::size_t> dims()    const { return a.dims();    }
};

template <typename T1, typename T2>
TensorCWiseProd<T1,T2> const operator*(const T1& a, const T2& b){
    return TensorCWiseProd<T1,T2>(a,b);
}

template<typename T1,typename T2>
class Traits<TensorCWiseProd<T1,T2>>{
public:
    using datatype = typename Traits<T1>::datatype;
};

#endif //TENSORCWISEPROD_H
