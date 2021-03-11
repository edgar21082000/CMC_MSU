#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

int main(void)
{
    int m, n;
    std::cin >> m >> n;
    int r1, c1, r2, c2;
    
    while(std::cin >> r1 >> c1 >> r2 >> c2){
        std::cout << std::min((abs(r1-r2)), (m - abs(r1-r2))) +
                std::min(abs(c1-c2), n - abs(c1-c2)) << std::endl; 
    }
    return 0;
}
