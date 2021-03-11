#include <iostream>

class S{
public:
    int k{}, sum{};
    bool flag = false;
    S(){
        flag = static_cast<bool>(std::cin >> k); 
        sum += k;
    }
    S(const S& cur) : sum(cur.sum){
        flag = static_cast<bool>(std::cin >> k); 
        sum += k;
    }
    ~S(){
        if(!flag and sum) 
            std::cout << sum << std::endl;
    }
    
    operator bool() {
        return flag;
    }
};

