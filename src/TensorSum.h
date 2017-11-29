#ifndef TENSORSUM_H
#define TENSORSUM_H
#include <cassert>
#include "TensorExpression.h"
#include "Traits.h"

namespace vc{

    template <typename T1, typename T2, typename Enable = void > class TensorSum;
    
    template<typename T1, typename T2>
    class TensorSum<T1,T2, typename std::enable_if_t<!std::is_arithmetic<T1>::value && !std::is_arithmetic<T2>::value>> : public TensorExpression<TensorSum<T1,T2>>{ //both not arithmetic type
    public:
        using datatype = typename Traits<TensorSum<T1,T2>>::datatype;
        const T1& lhs;
        const T2& rhs;
        TensorSum(const T1& u, const T2& v):lhs(u),rhs(v){
            assert(lhs.equalDims(rhs));
        }
        datatype operator[](int i) const { return lhs[i] + rhs[i]; }
        int size()                 const { return lhs.size();    }
        std::vector<int> dims()    const { return lhs.dims();    }
    };
    
    template<typename T1, typename T2>
    class TensorSum<T1,T2, typename std::enable_if_t<std::is_arithmetic<T1>::value && !std::is_arithmetic<T2>::value>> : public TensorExpression<TensorSum<T1,T2>>{ //lhs arithmetic type
    public:
        using datatype = typename Traits<TensorSum<T1,T2>>::datatype;
        const T1& lhs;
        const T2& rhs;
        TensorSum(const T1& u, const T2& v):lhs(u),rhs(v){}
        datatype operator[](int i) const { return lhs + rhs[i]; }
        int size()                 const { return rhs.size();    }
        std::vector<int> dims()    const { return rhs.dims();    }
    };
    
    template<typename T1, typename T2>
    class TensorSum<T1,T2, typename std::enable_if_t<!std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value>> : public TensorExpression<TensorSum<T1,T2>>{ //rhs arithmetic type
    public:
        using datatype = typename Traits<TensorSum<T1,T2>>::datatype;
        const T1& lhs;
        const T2& rhs;
        TensorSum(const T1& u, const T2& v):lhs(u),rhs(v){}
        datatype operator[](int i) const { return lhs[i] + rhs; }
        int size()                 const { return lhs.size();    }
        std::vector<int> dims()    const { return lhs.dims();    }
    };
    
    template <typename T1, typename T2>
    TensorSum<T1,T2> const operator+(const T1& lhs, const T2& rhs){
        return TensorSum<T1,T2>(lhs,rhs);
    }
    
    template<typename T1,typename T2>
    class Traits<TensorSum<T1,T2>, typename std::enable_if_t<!std::is_arithmetic<T1>::value>>{
    public:
        using datatype = typename Traits<T1>::datatype;
    };
    
    template<typename T1,typename T2>
    class Traits<TensorSum<T1,T2>, typename std::enable_if_t<std::is_arithmetic<T1>::value>>{
    public:
        using datatype = typename Traits<T2>::datatype;
    };

}

#endif //TENSORSUM_H
