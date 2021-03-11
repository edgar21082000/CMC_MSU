#include <iostream>
#include <vector>

void process(std::vector<long long> &v1,
        long long max_val){
    
    if(!v1.size())
        return;
    
    for(auto s1 = v1.end()-1; s1 >= v1.begin(); s1--){
        if (*s1 >= max_val){
            auto dif = s1 - v1.begin(); 
            v1.push_back(*s1);
            s1 = v1.begin() + dif;  
        }
    }
}


