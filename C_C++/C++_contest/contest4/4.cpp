#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

template<typename Iter_1, typename Iter_2>

Iter_2 myremove(Iter_1 first, Iter_1 last, Iter_2 start, Iter_2 fin){
    if(first == last or start == fin) return fin;
    
    std::vector<int> v1{};
    for(; first != last; first++)
        v1.emplace_back(*first);
    
    std::sort(v1.begin(), v1.end());
    std::unique(v1.begin(), v1.end());
    
    auto k = v1.begin();
    for(; *k < 0; k++)
        if (k == v1.end()) return fin;
        
    auto l = start;
    auto r = start;
    
    for(; r != fin; r++){
        if (k != v1.end() and (r - start == *k)) {
            k++;
        } else {
            std::iter_swap(l, r);
            l++;
        }    
    } 
    
    return l;
}



