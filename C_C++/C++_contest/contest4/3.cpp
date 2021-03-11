#include <vector>
//#include <functional>
//#include <iostream>

template<typename T, typename fun>

void 
myapply(T first, T last, fun f){
    while(first != last) f(*first++);
}

template<typename T, typename fun>

std::vector<std::reference_wrapper<typename std::iterator_traits<T>:: value_type>>
myfilter2(T first, T last, fun f){
    std::vector<std::reference_wrapper<typename std::iterator_traits<T>:: value_type>> res;    
    while(first != last){
        if(f(*first))
            res.push_back(*first);
        first++;
    }
    return res;
}

int main() {
    return 0;
}

