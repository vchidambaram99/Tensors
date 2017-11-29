#ifndef TENSOR_H
#define TENSOR_H
#include <vector>
#include <exception>
#include <iostream>
#include <sstream>
#include <cassert>
#include "TensorExpression.h"
#include "Traits.h"

namespace vc{

    template<typename T>
    class Tensor : public TensorExpression<Tensor<T>>{
    public:
        using datatype = typename Traits<Tensor<T>>::datatype;
        Tensor(){
            data = nullptr;
        }
        template<typename E>
        Tensor(const TensorExpression<E>& a){
            data = new T[a.size()];
            for(int i = 0;i<_size;i++){
                data[i] = static_cast<T>(a[i]);
            }
            _size = a.size();
            _dims = a.dims();
        }
        template<typename E>
        Tensor& operator=(const TensorExpression<E>& a){
            if(a.size()!=_size){
                delete data;
                data = new T[a.size()];
                _size = a.size();
            }
            _dims = a.dims();
            for(int i = 0;i<_size;i++){
                data[i] = a[i];
            }
            return *this;
        }
        Tensor(const std::vector<int>& dimensions){
            _size = 1;
            for(std::size_t i = 0;i<dimensions.size();i++){
                _size*=dimensions[i];
            }
            data = new T[_size];
            _dims = dimensions;
        }
        ~Tensor(){
            delete[] data;
        }
        T& operator[](int idx)        { return data[idx]; } //direct access to underlying array
        T  operator[](int idx)  const { return data[idx]; } //direct access to underlying array
        int size()              const { return _size;     } //size of underlying array (num elements in tensor)
        std::vector<int> dims() const { return _dims;     } //each dimension of tensor
        T* getData()                  { return data;      } //returns pointer to first element of data array

        template<typename E> Tensor& operator*=(const TensorExpression<E>& rhs){
            assert(this->equalDims(rhs));
            for(int i = 0;i<_size;i++){
                data[i] *= rhs[i];
            }
            return *this;
        }
        template<typename E> Tensor& operator/=(const TensorExpression<E>& rhs){
            assert(this->equalDims(rhs));
            for(int i = 0;i<_size;i++){
                data[i] /= rhs[i];
            }
            return *this;
        }
        template<typename E> Tensor& operator+=(const TensorExpression<E>& rhs){
            assert(this->equalDims(rhs));
            for(int i = 0;i<_size;i++){
                data[i] += rhs[i];
            }
            return *this;
        }
        template<typename E> Tensor& operator-=(const TensorExpression<E>& rhs){
            assert(this->equalDims(rhs));
            for(int i = 0;i<_size;i++){
                data[i] -= rhs[i];
            }
            return *this;
        }

    private:
        T* data = nullptr;
        int _size = 0;
        std::vector<int> _dims;
    };

    template<typename T>
    class Traits<Tensor<T>>{
    public:
        using datatype = T;
    };

}

#endif //TENSOR_H
