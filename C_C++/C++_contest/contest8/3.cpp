#include <iostream>
#include <cctype>

void eps_clear(std::string& str) {
    std::size_t idx = str.find("_");
    while (idx != std::string::npos) {
        str.erase(idx, 1);
        idx = str.find("_");
    }
}

bool has_t(std::string str){
    for(const char &c : str)
        if(islower(c)) 
            return true;
    return false;
}

bool has_nt(std::string str){
    for(const char &c : str)
        if(isupper(c))
            return true;
    return false;
}

bool has_S(std::string str){
    if (str.find('S') != std::string::npos) 
        return true;
    return false;
}

int main(void){
    
    bool empty_rules = true,
        empty_left = false,
        only_t_l = false,
        S_left = false;
        
    bool S_epsylon = false,
        type2 = false,
        S_r = false, 
        t_left = false,
        type23 = false; 
    
    std::string l_part, r_part;
    while(std::cin >> l_part >> r_part){
        empty_rules = false;
        eps_clear(l_part);
        eps_clear(r_part);
        
        bool t = has_t(l_part);
        bool nt = has_nt(l_part);
        if(t && !nt){
            only_t_l = true;
            break;
        }
        
        if(!l_part.length()){
            empty_left = true;
            break;
        }
        
        if(l_part == "S"){
            S_left = true;
            if(r_part == ""){
                S_epsylon = true;
                continue;
            }
        }
        //--------------------
        
         
        S_r |= has_S(r_part); 
         
        if(l_part.length() > r_part.length())
            type2 = true; 
        
        if (t)
            t_left = true;
            
        if(l_part.length() > 1)
            type23 = true;
    }
    
    if(S_epsylon && S_r)
        type2 = true;
        
    //------------------
    if(empty_rules || only_t_l || empty_left || !S_left)
        std::cout << -1 << std::endl;
    else if(type2 && !type23 && !t_left)
        std::cout << 2 << std::endl;
    else if(!type23 && !t_left)
        std::cout << 23 << std::endl;
    else
        std::cout << 10 << std::endl;
        
    return 0;
    
}
