#include <iostream>
#include <cctype>

enum{
    INIT_MODE,
    CHECK_MODE,
    ERR_MODE,
};

int main(void){
    int mode = INIT_MODE;
    int init_0_cnt = 0, init_1_cnt = 0;
    int check_0_cnt = 0, check_1_cnt = 0;
    bool f_init = 0, f_check = 0;
    char c;
    
    while(1){
        c = std::getc(stdin);
        
        //printf("[mode %d], %c<%d> || i0c = %d, i1c = %d | c0c = %d, c1c = %d \n", 
        //        mode, c, c, init_0_cnt, init_1_cnt, check_0_cnt, check_1_cnt ); 
        
        if(isspace(c) || c == EOF){
            if (mode == ERR_MODE) 
                std::cout << "0" << std::endl;
                
            else if(mode == CHECK_MODE){
                if (init_1_cnt == check_1_cnt)
                    std::cout << "1" << std::endl;
                else
                    std::cout << "0" << std::endl;
                    
            } else if(mode == INIT_MODE ){
                if (init_0_cnt){
                    if (init_0_cnt == init_1_cnt)
                        std::cout << "1" << std::endl;
                    else
                        std::cout << "0" << std::endl;
                }          
            }
                
                
            init_0_cnt = 0; init_1_cnt = 0;
            check_0_cnt = 0, check_1_cnt = 0;
            f_init = false, f_check = false;
            
            if (c == EOF) break; 
            
            mode = INIT_MODE;
        
        } else if (mode == INIT_MODE){
            if (c == '0' || c == '1'){
                if (c == '0'){
                    if (f_init){
                        check_0_cnt++;
                        mode = CHECK_MODE;
                    } else {
                        //f_init = false;
                        init_0_cnt++;
                    }   
                } 
                     
                if (c == '1'){
                    if(!init_0_cnt)
                        mode = ERR_MODE;
                    else {
                        f_init = true;
                        init_1_cnt++;
                    }
                        
                }
            } else 
                mode = ERR_MODE;
        
        } else if (mode == CHECK_MODE){
            if (c == '0' || c =='1'){
                if (c == '0'){
                    if(f_check && (init_1_cnt != check_1_cnt)){
                        mode = ERR_MODE;    
                    } else {
                        //f_check = false;
                        if(f_check){
                            check_0_cnt = 0;
                            check_1_cnt = 0;
                            f_check = false;
                        }
                        check_0_cnt++;    
                    }
                    
                }
                
                if (c == '1'){
                    f_check = true; 
                    if (init_0_cnt != check_0_cnt)
                        mode = ERR_MODE;
                    else
                        check_1_cnt++;
                }
            } else
                mode = ERR_MODE;
        }
        
    }
    
    return 0;
}
