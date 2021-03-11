#include <iostream>
#include <vector>
#include <cstdint>

//using namespace std;

void process(std::vector<uint64_t> &v,  uint32_t s){
    if(!v.size() or s > v.size()) return;
    
    uint64_t sum = 0;
    uint32_t dist = s;
    
    auto it = v.begin();
    
    while(it != v.end()){
        sum += *it; 
        dist--;
        if(!dist){
            it = v.insert(++it, sum);
            dist = s;     
        }
        it++;
    }
    return ;
}

