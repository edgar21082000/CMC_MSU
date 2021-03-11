// L = {a^n0^mb^n1^m | n, m > 0}
//S -> aSb | a0Cb
//C -> 0C
//Cb -> CD
//CD -> bD
//bD -> bC
//bC -> b1
//1C -> 11
#include <iostream>

int main(void){
    
    std::string cur;
    while(std::cin >> cur){
        enum struct St{
            empty,
            a, b, zero, one,
            err,
        } state = St::empty;
        
        struct Cnt_st{
            int a = 0;
            int zero = 0;
            int b = 0;
            int one = 0;
        } cnt;
        
        for(char c : cur){
            switch(state){
            
            case(St::empty):
                switch(c){
                case('a'):
                    state = St::a;
                    cnt.a++;
                    break;
                default:
                    state = St::err;
                    break;
                }
                break;
            case(St::a):
                switch(c){
                case('a'):
                    cnt.a++;
                    break;
                case('0'):
                    state = St::zero;
                    cnt.zero++;
                    break;
                default:
                    state = St::err; 
                    break;
                }
                break;    
            case(St::zero): 
                switch(c){
                case('0'):
                    cnt.zero++;
                    break;
                case('b'):
                    state = St::b;
                    cnt.b++;
                    break;
                default:
                    state = St::err;
                    break;
                }
                break;
            case(St::b):
                switch(c){
                case('b'):
                    cnt.b++;
                    break;
                case('1'):
                    if(cnt.b != cnt.a){
                        state = St::err; 
                        break;
                    } else {
                        state = St::one;
                        cnt.one++;
                        break;
                    }
                    break;
                default:
                    state = St::err; 
                    break;
                }
                break;
            case(St::one):
                switch(c){
                case('1'):
                    cnt.one++;
                    break;
                default:
                    state = St::err; 
                    break;
                }
                break;
            case(St::err):
                break;
            }
        }
        bool ans = (state != St::err) && (cnt.zero == cnt.one) && (cnt.a == cnt.b); 
        std::cout << ans << std::endl;
    }
    return 0;
}
