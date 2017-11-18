#ifndef TENSOREXPRESSION_H
#define TENSOREXPRESSION_H
#include <vector>
#include "Tensor.h"
#include "Traits.h"

template<typename T> //T is TensorSum,TensorCWiseProd,etc.
class TensorExpression{
public:
    using datatype = typename Traits<T>::datatype;
    virtual ~TensorExpression(){}
    datatype operator[](std::size_t i) const { return static_cast<const T&>(*this)[i];     } //returns evaluation of tensor expression
    std::size_t size()                 const { return static_cast<const T&>(*this).size(); } //returns size of data array
    std::vector<std::size_t> dims()    const { return static_cast<const T&>(*this).dims(); } //returns dims of data array
    operator T& ()                           { return static_cast<T&>(*this);              }
    operator const T& ()               const { return static_cast<const T&>(*this);        }

    template<typename E>
    bool equalDims(const TensorExpression<E>& rhs) const { //checks if dims of this and another tensor are the same (necessary for cwise operations)
        std::vector<std::size_t> dims1 = rhs.dims();
        std::vector<std::size_t> dims2 = dims();
        if(dims1.size()!=dims2.size())return false;
        for(std::size_t i = 0;i<dims1.size();i++){
            if(dims1[i]!=dims2[i])return false;
        }
        return true;
    }
};

#endif //TENSOREXPRESSION_H
