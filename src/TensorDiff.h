#ifndef TENSORDIFF_H
#define TENSORDIFF_H
#include "DimsException.h"
#include "TensorExpression.h"
#include "Traits.h"

template <typename T1, typename T2, typename Enable = void > class TensorDiff;

template<typename T1, typename T2>
class TensorDiff<T1,T2, typename std::enable_if_t<!std::is_arithmetic<T1>::value && !std::is_arithmetic<T2>::value>> : public TensorExpression<TensorDiff<T1,T2>>{ //both not arithmetic type
public:
    using datatype = typename Traits<TensorDiff<T1,T2>>::datatype;
    const T1& a;
    const T2& b;
    TensorDiff(const T1& u, const T2& v):a(u),b(v){
        if(!a.equalDims(b))throw DimsException(a.dims(),b.dims());
    }
    datatype operator[](std::size_t i) const { return a[i] - b[i]; }
    std::size_t size()                 const { return a.size();    }
    std::vector<std::size_t> dims()    const { return a.dims();    }
};

template<typename T1, typename T2>
class TensorDiff<T1,T2, typename std::enable_if_t<std::is_arithmetic<T1>::value && !std::is_arithmetic<T2>::value>> : public TensorExpression<TensorDiff<T1,T2>>{ //lhs arithmetic type
public:
    using datatype = typename Traits<TensorDiff<T1,T2>>::datatype;
    const T1& a;
    const T2& b;
    TensorDiff(const T1& u, const T2& v):a(u),b(v){}
    datatype operator[](std::size_t i) const { return a - b[i]; }
    std::size_t size()                 const { return b.size();    }
    std::vector<std::size_t> dims()    const { return b.dims();    }
};

template<typename T1, typename T2>
class TensorDiff<T1,T2, typename std::enable_if_t<!std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value>> : public TensorExpression<TensorDiff<T1,T2>>{ //rhs arithmetic type
public:
    using datatype = typename Traits<TensorDiff<T1,T2>>::datatype;
    const T1& a;
    const T2& b;
    TensorDiff(const T1& u, const T2& v):a(u),b(v){}
    datatype operator[](std::size_t i) const { return a[i] - b; }
    std::size_t size()                 const { return a.size();    }
    std::vector<std::size_t> dims()    const { return a.dims();    }
};

template <typename T1, typename T2>
TensorDiff<T1,T2> const operator-(const T1& a, const T2& b){
    return TensorDiff<T1,T2>(a,b);
}

template<typename T1,typename T2>
class Traits<TensorDiff<T1,T2>, typename std::enable_if_t<!std::is_arithmetic<T1>::value>>{
public:
    using datatype = typename Traits<T1>::datatype;
};

template<typename T1,typename T2>
class Traits<TensorDiff<T1,T2>, typename std::enable_if_t<std::is_arithmetic<T1>::value>>{
public:
    using datatype = typename Traits<T2>::datatype;
};

#endif //TENSORDIFF_H
