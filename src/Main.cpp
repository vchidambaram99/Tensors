#include <iostream>
#include "Tensors"
using namespace std;

int main(){ //TODO implement an array class with a shared smart pointer so d won't become invalid after the cwise operation!!!!! (and so I wont worry abouut deleting twice or never)
            //TODO implement contracion
            //TODO implement reshaping
            //TODO implement blocking
            //TODO implement get element (parentheses operator? function taking std::vector? both?)
    vc::Tensor<double> a({3,3,3});
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            for(int k = 0;k<3;k++){
                a[9*i+3*j+k] = 9*i+3*j+k;
                cout<<9*i+3*j+k<<endl;
            }
        }
    }
    cout<<endl;
    a*=a;
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            for(int k = 0;k<3;k++){
                cout<<a[9*i+3*j+k]<<endl;
            }
        }
    }
    return 0;
}
