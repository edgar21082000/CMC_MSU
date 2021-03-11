#include <iostream>

class Foo{
public:
    long long res;
    Foo(long long res_) : res(res_) {}
    ~Foo(){}
};

void func(long long a, long long b, int k){

    if (k == 0){
        throw Foo(a+b);
    } else if (k > 0 and b == 1){
        throw Foo(a);
    } else {
        try{
            func(a, b-1, k);
        } catch (Foo foo) {
            func(a, foo.res, k-1);
        }
    }
}



int main(void){
    long long a, b;
    int k;
    while(std::cin >> a >> b >> k){
        try{
            func(a, b, k);
        } catch (Foo foo){
            std::cout << foo.res << std::endl;
        }  
    }
    return 0;
}
