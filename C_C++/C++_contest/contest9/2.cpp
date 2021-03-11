#include <iostream>

int main(void){
    std::string cur;
    
    while(std::cin >> cur){
        enum struct St{
            H, A, Bfantom, Cfantom, Sfantom, ERR,
        } state = St::H;
        
        for(char c : cur){
            switch(state){
            case(St::H):
                switch(c){
                case('0'):
                    state = St::A;
                    break;
                case('1'):
                    state = St::Bfantom;
                    break;
                default:
                    state = St::ERR;
                    break;
                }
                break;
            case(St::A):
                switch(c){
                case('0'):
                    state = St::A;
                    break;
                case('1'):
                    state = St::Bfantom;
                    break;
                default:
                    state = St::ERR;
                    break;
                }
                break;
            case(St::Bfantom):
                switch(c){
                case('0'):
                case('1'):
                    state = St::Cfantom;
                    break;
                default:
                    state = St::ERR;
                    break;
                }
                break;
            case(St::Cfantom):
                switch(c){
                case('0'):
                case('1'):
                    state = St::Sfantom;
                    break;
                default:
                    state = St::ERR;
                    break;
                }
                break;
            case(St::Sfantom):
                switch(c){
                case('0'):
                case('1'):
                    state = St::Sfantom;
                    break;
                default:
                    state = St::ERR;
                    break;
                }
                break;
            case(St::ERR):
                break;    
            }
        }
        std::cout << (state == St::Sfantom) << std::endl;
    }
    return 0;
}
