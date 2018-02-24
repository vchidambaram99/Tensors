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
        Tensor(const Tensor<T>& a){ //Copy-construction (the templated TensorExpression version doesn't work for this)
            _size = a.size();
            _dims = a.dims();
            _strides = a.strides();
            data = new T[_size];
            #pragma omp parallel for simd
            for(int i = 0;i<_size;i++){
                data[i] = a[i];
            }
        }
        Tensor& operator=(const Tensor<T>& a){ //Assignment (the templated TensorExpression version doesn't work for this)
            if(a.size()!=_size){
                delete data;
                data = new T[a.size()];
                _size = a.size();
            }
            _dims = a.dims();
            _strides = a.strides();
            #pragma omp parallel for simd
            for(int i = 0;i<_size;i++){
                data[i] = a[i];
            }
            return *this;
        }
        template<typename E>
        Tensor(const TensorExpression<E>& a){ //evaluates TensorExpression and stores result in this tensor
            _size = a.size();
            _dims = a.dims();
            _strides = a.strides();
            data = new T[_size];
            #pragma omp parallel for simd
            for(int i = 0;i<_size;i++){
                data[i] = a[i]; //performs evaluation of each element of the TensorExpression
            }
        }
        template<typename E>
        Tensor& operator=(const TensorExpression<E>& a){ //evaluates TensorExpression and stores result in this tensor
            //NOTE: This is different from the above constructors in case of a = a.reduce(a,{something});
            int newSize = a.size();
            T* newData = new T[newSize];
            #pragma omp parallel for simd
            for(int i = 0;i<newSize;i++){
                newData[i] = a[i]; //performs evaluation of each element of the TensorExpression
            }
            delete data;
            data = newData;
            _size = newSize;
            _dims = a.dims();
            _strides = a.strides();
            return *this;
        }
        Tensor(const std::vector<int>& dimensions){ //constructs tensor with specified dimensions (default-initialized elements)
            _size = 1;
            for(std::size_t i = 0;i<dimensions.size();i++){
                _size*=dimensions[i];
            }
            data = new T[_size]();
            _dims = dimensions;
            setStriding();
        }
        ~Tensor(){
            delete[] data;
        }
        T& operator[](int idx)           { return data[idx]; } //direct access to underlying array
        T  operator[](int idx)     const { return data[idx]; } //direct access to underlying array
        int size()                 const { return _size;     } //size of underlying array (num elements in tensor)
        std::vector<int> dims()    const { return _dims;     } //each dimension of tensor
        std::vector<int> strides() const { return _strides;  } //returns the striding of the tensor
        T* getData()                     { return data;      } //returns pointer to first element of data array ***OFTEN UNSAFE AFTER ASSIGNMENT (data may get delete[]d)***

        template<typename E> Tensor& operator*=(const E& rhs){
            *this = *this * rhs;
            return *this;
        }
        template<typename E> Tensor& operator/=(const E& rhs){
            *this = *this / rhs;
            return *this;
        }
        template<typename E> Tensor& operator+=(const E& rhs){
            *this = *this + rhs;
            return *this;
        }
        template<typename E> Tensor& operator-=(const E& rhs){
            *this = *this - rhs;
            return *this;
        }
        T& operator()(const std::vector<int>& pos){ //element-wise access (the vector has the value for each dimension (0-based))
            assert(pos.size()==_dims.size());
            int idx = 0;
            for(std::size_t i = 0;i<pos.size();i++){
                idx+=pos[i]*_strides[i];
            }
            return data[idx];
        }
        T operator()(const std::vector<int>& pos) const { //element-wise access (the vector has the value for each dimension (0-based))
            assert(pos.size()==_dims.size());
            int idx = 0;
            for(std::size_t i = 0;i<pos.size();i++){
                idx+=pos[i]*_strides[i];
            }
            return data[idx];
        }

    private:
        T* data = nullptr;
        int _size = 0;
        std::vector<int> _dims;
        std::vector<int> _strides;
        void setStriding(){ //sets the strides for the tensor
            _strides = std::vector<int>(_dims.size());
            _strides.back() = 1;
            for(int i = _strides.size()-2;i>=0;i--){
                _strides[i] = _strides[i+1]*_dims[i+1];
            }
        }
    };

    template<typename T>
    class Traits<Tensor<T>>{
    public:
        using datatype = T;
    };

}

#endif //TENSOR_H
