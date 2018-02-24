#ifndef TENSORREDUCTION_H
#define TENSORREDUCTION_H
#include <vector>
#include <cassert>
#include "TensorExpression.h"
#include "Traits.h"

namespace vc{

    template<typename T>
    class TensorReduction : public TensorExpression<TensorReduction<T>>{
    public:
        using datatype = typename Traits<TensorReduction<T>>::datatype;
        const T& argument; //tensor to be reduced
        const std::vector<int>& redIdxs; //reduction indices
        std::vector<int> inputDims; //dimensions of input
        std::vector<int> inputStrides; //strides of input
        std::vector<int> retDims; //dimensions of output
        std::vector<int> retStrides; //strides of output
        std::vector<int> nonRedStrides; //strides of input that aren't being reduced
        int _size;
        TensorReduction(const T& arg, const std::vector<int>& idxs):argument(arg),redIdxs(idxs){
            //returns the tensor summed over the given indices (all indices if none are given)
            if(redIdxs.size()==0){
                retDims = {1};
                retStrides = {1};
                _size = 1;
            }else{
                inputDims = argument.dims();
                inputStrides = argument.strides();
                retDims = std::vector<int>(inputDims.size()-redIdxs.size());
                nonRedStrides = std::vector<int>(retDims.size());
                std::size_t idx = 0;
                std::vector<bool> reductionMask(inputDims.size(),false);
                for(std::size_t i = 0;i<redIdxs.size();i++){
                    reductionMask[redIdxs[i]] = true;
                }
                for(std::size_t i = 0;i<inputDims.size();i++){ //iterates over dimensions of argument
                    if(!reductionMask[i]){
                        retDims[idx] = inputDims[i]; //adds to output dims if it isn't a reduction index
                        nonRedStrides[idx] = inputStrides[i];
                        ++idx;
                    }
                }
                assert(retDims.size()==idx && "EACH INDICE MUST BE UNIQUE");
                if(retDims.size()==0){
                    retDims = {1};
                    retStrides = {1};
                    _size = 1;
                }
                retStrides = std::vector<int>(retDims.size());
                retStrides.back() = 1;
                for(std::size_t i = retStrides.size()-1;i-->0;){
                    retStrides[i] = retDims[i+1]*retStrides[i+1];
                }
                _size = retStrides[0]*retDims[0];
            }
        }
        datatype operator[](int idx) const { //evaluates an element of the expression TODO test, TODO bench
            assert(idx<_size && "INDEX OUT OF BOUNDS");
            if(_size==1){
                datatype ret = datatype();
                #pragma omp parallel for simd
                for(int i = 0;i<argument.size();i++){
                    ret+=argument[i];
                }
                return ret;
            }
            int start = 0;
            for(std::size_t i = 0;i<nonRedStrides.size();i++){ //TODO bench a version where starts are precomputed (using recursive for loop)
                start+=nonRedStrides[i]*(idx/retStrides[i]);
                idx%=retStrides[i];
            }
            return sumHelper(0,start);
        }
        std::vector<int> dims()    const { return retDims;    } //returns the dims of the expression
        int size()                 const { return _size;      } //returns what the size of the underlying array would be
        std::vector<int> strides() const { return retStrides; } //returns strides of the expression
        datatype sumHelper(std::size_t rIdx, int startPos) const { //sums over the subspace given in redIdxs[>=rIdx], starting at position start (basically an arbitrary number of for-loops)
            if(rIdx==redIdxs.size())return argument[startPos];
            int idx = redIdxs[rIdx];
            datatype total = datatype();
            #pragma omp simd
            for(int i = 0;i<inputDims[idx];i++){
                total+=sumHelper(rIdx+1,startPos+i*inputStrides[idx]);
            }
            return total;
        }
    };

    template<typename T>
    class Traits<TensorReduction<T>>{
    public:
        using datatype = typename Traits<T>::datatype;
    };

}

#endif //TENSORREDUCTION_H
