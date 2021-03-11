#include <iostream>
#include <vector>
#include <cctype>
#include <map>

int main(void){
    std::vector<std::pair<char, std::string>> rules;
    char left; std::string right;
    std::vector<char> term;
    term.push_back('S');
    
    while(std::cin >> left >> right)
        rules.push_back(std::pair<char, std::string>(left, right));
        
        
    bool change = true; size_t idx=0;    
    while(change){
        change = false;
        if(idx == term.size()) break;
        
        for(auto r : rules){
            if(term[idx] == r.first){
                for(char c : r.second){ 
                    if(isupper(c)){
                        bool add = true;
                        for(size_t i=0; i<term.size(); i++){
                            if(c == term[i]) add = false;
                        }
                        if(add){
                            term.push_back(c);
                            change = true;   
                        }
                    }
                }
            }
            if(change) {idx++; break;}
        }
        
    }
    
    for(auto r : rules){
        bool print = false;
        for(auto t : term){
            if(r.first == t){
                print = true;
                break;
            }
        }
        if(print) std::cout << r.first << " " << r.second << std::endl;
    }
    return 0;
}
