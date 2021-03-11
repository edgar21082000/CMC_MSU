#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <array>

namespace Equations{
    
    template<typename T>
    
    std::pair<bool, std::vector<std::complex<T>>> 
    quadratic(std::array<std::complex<T>, 3> v){
        bool success = true;
        std::vector<std::complex<T>> res;
        
        std::complex<T> c = v[0], b = v[1], a = v[2];
        
        if (a == static_cast<T>(0.) && b == static_cast<T>(0.) && c == static_cast<T>(0.)){
            success = false;
            return std::make_pair(success, res);
        }
        
        if (a == static_cast<T>(0.) && b == static_cast<T>(0.) && c != static_cast<T>(0.)){
            return std::make_pair(success, res);
        }
        
        if (a == static_cast<T>(0.)){
            std::complex<T> z1 = -c / b;
            res.push_back(z1);
            return std::make_pair(success, res);
        }
        
        std::complex<T> D = b*b - static_cast<T>(4.)*a*c;
        std::complex<T> z1 = (-b + std::sqrt(D)) / (static_cast<T>(2.)*a);
        std::complex<T> z2 = (-b - std::sqrt(D)) / (static_cast<T>(2.)*a);
        
        res.push_back(z1);
        res.push_back(z2);
        
        return std::make_pair(success, res);
    }
       
}

