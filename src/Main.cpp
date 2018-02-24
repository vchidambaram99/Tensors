#include <iostream>
#include "Tensors"
#include <eigen3/bench/BenchTimer.h>
#include <unsupported/Eigen/CXX11/Tensor>
#include <cmath>
using namespace std;

int main(){ //TODO implement contracion
            //TODO implement reshaping
            //TODO implement blocking
            //TODO generalize binary operations
            //TODO write stuff that takes advantage of simd intrinsics without help from compiler
            //TODO add other operations
    srand(time(0));
    double mt = 0,et = 0;
    for(int x = 0;x<100;x++){
        vc::Tensor<double> a({30,30,30});
        Eigen::Tensor<double,3> b(30,30,30);
        vc::Tensor<double> a1;
        Eigen::Tensor<double,3> b1;
        for(int i = 0,end = a.dims()[0];i<end;i++){
            for(int j = 0,end = a.dims()[1];j<end;j++){
                for(int k = 0,end = a.dims()[2];k<end;k++){
                    a({i,j,k}) = (rand()/327.67)-50;
                    b(i,j,k) = a({i,j,k});
                }
            }
        }
        Eigen::BenchTimer t1,t2;
        BENCH(t1, 5, 5, a1=a*a );
        BENCH(t2, 5, 5, b1=b*b );
        mt+=t1.best();
        et+=t2.best();
        for(int i = 0;i<a1.dims()[0];i++){
            for(int j = 0;j<a1.dims()[1];j++){
                for(int k = 0;k<a1.dims()[2];k++){
                    if(a1({i,j,k}) != b1(i,j,k)){
                        cout<<a1({i,j,k})<<" "<<b1(i,j,k)<<endl;
                    }
                }
            }
        }
    }
    cout << "Time taken by mine  is: " << mt << endl;
    cout << "Time taken by Eigen is: " << et << endl;
    cout << "Ratio: " << mt/et <<endl;
    return 0;
}
