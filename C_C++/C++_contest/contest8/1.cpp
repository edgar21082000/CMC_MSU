#include <iostream>
#include <cctype>

int main(void){
    int mode = 0;
    
    do{
        //printf("[%d] %d -  '%c'\n", mode, c, c);
        char c =  std::getc(stdin); 
        if(isspace(c) || c == EOF){
            if(mode == 12 || mode == 34)
                std::cout << 1 <<  std::endl;
            if(c == EOF) break;
            mode = 0;
            
        } else if (mode == 0){
            if(c == '3' || c == '4') mode = 34;
            else if(c == '1' || c == '2') mode = 12;
            else {mode = -1; std::cout << 0 << std::endl;}
            
        } else if(mode == 34){
            if(c == '3' || c == '4'){}
            else if((c == '1' || c == '2')) mode = 12;
            else {mode = -1; std::cout << 0 << std::endl;}
            
        } else if (mode == 12){
            if(c == '1' || c == '2'){}
            else {mode = -1; std::cout << 0 << std::endl;}    
        }
    }while(1);
    
    return 0;
}
