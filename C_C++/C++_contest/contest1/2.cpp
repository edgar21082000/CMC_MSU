#include <iostream>    

class Sub {
private:
    int res;
public:
    Sub(int a, int b) : res(a-b) {}
    
    Sub(Sub a, int b) : res(a.res - b) {}
    
    Sub(int a, Sub b) : res(a - b.res) {}
    
    int value() const {
        return res;
    }
            
};

