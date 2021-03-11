#include <iostream>
#include <map>
#include <vector>

int main(void){
    std::map<std::pair<std::string, char>, std::string> rules;
    std::string cur, next; char c;
    
    while(1){
        std::cin >> cur;
        if(cur == "END") break;
        std::cin >> c >> next;
        
        rules.insert(std::pair<std::pair<std::string, char>, std::string>
                (std::pair<std::string, char>(cur, c), next));
    }
    
    std::vector<std::string> fstate;
    while(1){
        std::cin >> cur;
        if(cur == "END") break;
        fstate.push_back(cur);
    }
    
    std::string cstate;
    std::cin >> cstate;
    
    std::string str;
    std::cin >> str;
    
    int cnt = 0;
    
    for(char c : str){
        auto it = rules.find(std::pair<std::string, char>(cstate, c));
        if(it == rules.end()) {
            std::cout << 0 << std::endl;
            std::cout << cnt << std::endl;
            std::cout << cstate << std::endl; 
            return 0;   
        }
        
        cstate = (*it).second;
        cnt++;
    }
    
    for(auto &str : fstate){
        if(str == cstate){
            std::cout << 1 << std::endl;
            std::cout << cnt << std::endl;
            std::cout << cstate << std::endl; 
            return 0;
        }
    }
    
    std::cout << 0 << std::endl;
    std::cout << cnt << std::endl;
    std::cout << cstate << std::endl; 
    
    return 0;
}
