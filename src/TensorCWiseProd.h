#ifndef TENSORCWISEPROD_H
#define TENSORCWISEPROD_H
#include <cassert>
#include "TensorExpression.h"
#include "Traits.h"

namespace vc{

    template <typename T1, typename T2, typename Enable = void > class TensorCWiseProd;

    template<typename T1, typename T2>
    class TensorCWiseProd<T1,T2, typename std::enable_if_t<!std::is_arithmetic<T1>::value && !std::is_arithmetic<T2>::value>> : public TensorExpression<TensorCWiseProd<T1,T2>>{ //both not arithmetic type
    public:
        using datatype = typename Traits<TensorCWiseProd<T1,T2>>::datatype;
        const T1& lhs;
        const T2& rhs;
        TensorCWiseProd(const T1& u, const T2& v):lhs(u),rhs(v){
            assert(lhs.equalDims(rhs));
        }
        datatype operator[](int i) const { return lhs[i] * rhs[i]; } //evaluates an element of the expression
        int size()                 const { return lhs.size();      } //returns what the size of the underlying array would be
        std::vector<int> dims()    const { return lhs.dims();      } //returns the dims of the expression
        std::vector<int> strides() const { return lhs.strides();   } //returns strides of the expression
    };

    template<typename T1, typename T2>
    class TensorCWiseProd<T1,T2, typename std::enable_if_t<std::is_arithmetic<T1>::value && !std::is_arithmetic<T2>::value>> : public TensorExpression<TensorCWiseProd<T1,T2>>{ //lhs arithmetic type
    public:
        using datatype = typename Traits<TensorCWiseProd<T1,T2>>::datatype;
        const T1& lhs;
        const T2& rhs;
        TensorCWiseProd(const T1& u, const T2& v):lhs(u),rhs(v){}
        datatype operator[](int i) const { return lhs * rhs[i];  } //evaluates an element of the expression
        int size()                 const { return rhs.size();    } //returns what the size of the underlying array would be
        std::vector<int> dims()    const { return rhs.dims();    } //returns the dims of the expression
        std::vector<int> strides() const { return rhs.strides(); } //returns strides of the expression
    };

    template<typename T1, typename T2>
    class TensorCWiseProd<T1,T2, typename std::enable_if_t<!std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value>> : public TensorExpression<TensorCWiseProd<T1,T2>>{ //rhs arithmetic type
    public:
        using datatype = typename Traits<TensorCWiseProd<T1,T2>>::datatype;
        const T1& lhs;
        const T2& rhs;
        TensorCWiseProd(const T1& u, const T2& v):lhs(u),rhs(v){}
        datatype operator[](int i) const { return lhs[i] * rhs;  } //evaluates an element of the expression
        int size()                 const { return lhs.size();    } //returns what the size of the underlying array would be
        std::vector<int> dims()    const { return lhs.dims();    } //returns the dims of the expression
        std::vector<int> strides() const { return lhs.strides(); } //returns strides of the expression
    };

    template <typename T1, typename T2>
    TensorCWiseProd<T1,T2> const operator*(const T1& lhs, const T2& rhs){
        return TensorCWiseProd<T1,T2>(lhs,rhs);
    }

    template<typename T1,typename T2>
    class Traits<TensorCWiseProd<T1,T2>, typename std::enable_if_t<!std::is_arithmetic<T1>::value>>{
    public:
        using datatype = typename Traits<T1>::datatype;
    };

    template<typename T1,typename T2>
    class Traits<TensorCWiseProd<T1,T2>, typename std::enable_if_t<std::is_arithmetic<T1>::value>>{
    public:
        using datatype = typename Traits<T2>::datatype;
    };

}

#endif //TENSORCWISEPROD_H
