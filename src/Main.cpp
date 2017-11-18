#include <iostream>
#include "Tensors"
using namespace std;

int main(){ //TODO TODO TODO implement an array class with a shared smart pointer so d won't become invalid after the multiplication!!!!!
            //TODO implement the rest of the cwise operations
    vector<size_t> dims = {2,2};
    Tensor<double> tensor(dims);
    double* d = tensor.getData();
    for(int i = 0;i<tensor.size();i++){
        d[i] = i+1;
        cout<<d[i]<<" ";
    }
    cout<<endl;
    tensor = tensor*tensor*tensor;
    d = tensor.getData();
    for(int i = 0;i<tensor.size();i++){
        cout<<d[i]<<" ";
    }
    cout<<endl;
    return 0;
}
