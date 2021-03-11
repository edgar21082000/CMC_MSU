#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

int main(int argc, char **argv)
{
    const double pi = 4 * atan(-1.);
    
    numbers::complex C(argv[1]);
    double R; 
    int N;
    std::vector<std::string> f(argc - 4);
    
    sscanf(argv[2], "%lf", &R);
    sscanf(argv[3], "%d", &N);
    
    int cnt = f.size();
    for (int i = 0; i < cnt; i++)
        f[i] = argv[i+4];
        
    numbers::complex z1(C.re(), C.im() + R), I;
    for (int i = 0; i < N; i++){
        numbers::complex z2(C + numbers::complex(R*sin(2*pi*(i + 1)/N), 
                R*cos(2*pi*(i + 1)/N) ));
        
        I += (z2 - z1)*eval(f, z2);
        z1 = z2;       
    }
    std::cout<<I.to_string()<<std::endl;
    return 0;
}
