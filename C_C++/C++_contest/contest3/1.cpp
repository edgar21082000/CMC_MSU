#include <vector>

void process(const std::vector<unsigned long long> &v1, 
        std::vector<unsigned long long> &v2, unsigned long long step){
    
    if(!v2.size())
        return;
    
    std::vector<unsigned long long>::const_iterator s1 = v1.begin();
    std::vector<unsigned long long>::reverse_iterator s2 = v2.rbegin();
    
    while(s1 < v1.end()){
        *s2 += *s1;
        if(++s2 == v2.rend())
            break;
        for(unsigned long long i=0; i<step; i++) s1++;
    }   
}
