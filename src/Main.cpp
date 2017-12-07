#include <iostream>
#include "Tensors"
#include <eigen3/bench/BenchTimer.h>
#include <unsupported/Eigen/CXX11/Tensor>
#include <cmath>
using namespace std;

int main(){ //TODO implement contracion
            //TODO implement reshaping
            //TODO implement blocking
            //TODO implement get element (function taking const std::vector&)
    srand(0);
    double mt = 0,et = 0;
    for(int x = 0;x<100;x++){
        vc::Tensor<double> a({30,30,30});
        Eigen::Tensor<double,3> b(30,30,30);
        b.setRandom();
        for(int i = 0,end = a.dims()[0];i<end;i++){
            for(int j = 0,end = a.dims()[1];j<end;j++){
                for(int k = 0,end = a.dims()[2];k<end;k++){
                    a({i,j,k}) = (rand()/327.67)-50;
                    b(i,j,k) = a({i,j,k});
                }
            }
        }
        Eigen::BenchTimer t1,t2;
        BENCH(t1, 5, 5, a=a*2 );
        BENCH(t2, 5, 5, b=b+b );
        mt+=t1.best();
        et+=t2.best();
        for(int i = 0,end = a.dims()[0];i<end;i++){
            for(int j = 0,end = a.dims()[1];j<end;j++){
                for(int k = 0,end = a.dims()[2];k<end;k++){
                    if(a({i,j,k}) != b(i,j,k)){
                        cout<<a({i,j,k})<<" "<<b(i,j,k)<<endl;
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
