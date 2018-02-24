#ifndef TENSOREXPRESSION_H
#define TENSOREXPRESSION_H
#include <vector>
#include "Tensor.h"
#include "Traits.h"

namespace vc{

    template<typename T> //T is TensorSum,TensorCWiseProd,etc.
    class TensorExpression{
    public:
        using datatype = typename Traits<T>::datatype;
        virtual ~TensorExpression(){}
        datatype operator[](int i) const { return static_cast<const T&>(*this)[i];        } //returns evaluation of an element in the tensor expression
        int size()                 const { return static_cast<const T&>(*this).size();    } //returns what the size of the underlying data array would be (no evaluation)
        std::vector<int> dims()    const { return static_cast<const T&>(*this).dims();    } //returns the dims of the expression (no evaluation)
        std::vector<int> strides() const { return static_cast<const T&>(*this).strides(); } //returns strides of the tensor expression (no evaluation)

        template<typename E>
        bool equalDims(const TensorExpression<E>& rhs) const { //checks if dims of this and another tensor are the same (necessary for cwise operations)
            std::vector<int> dims1 = rhs.dims();
            std::vector<int> dims2 = dims();
            if(dims1.size()!=dims2.size())return false;
            for(std::size_t i = 0;i<dims1.size();i++){
                if(dims1[i]!=dims2[i])return false;
            }
            return true;
        }
    };

}

#endif //TENSOREXPRESSION_H
