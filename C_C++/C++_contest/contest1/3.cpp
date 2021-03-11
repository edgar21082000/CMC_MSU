#include <iostream>
class A {
private:
    int val, flag;
public:
    A() : flag(0){
        std::cin >> val;
    }
    A(const A& a) : flag(1){
        std::cin >> val;
        val += a.val;
    }
    ~A(){
        if(flag)
            std::cout<<val<<std::endl;
    }
};

