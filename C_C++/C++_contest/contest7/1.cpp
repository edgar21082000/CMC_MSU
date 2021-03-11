#include <iostream>
#include <string>

class Foo{
    std::string str;
    
public:
    Foo(std::string str_) : str(str_) {}
        
    ~Foo(){
        std::cout << str << std::endl;
    }
};

void rec(){
    std::string tmp;
    if (std::cin >> tmp) {
        Foo foo(tmp);
        rec();
    } else {
        throw 42;
    }
    
}

int main(void){
    try{
        rec();
    } catch (int excp){
        
    }
    return 0;
}
