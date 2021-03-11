#include <iostream>
#include <vector>


struct Rule{
    char c_st;
    char c_val;
    char n_st;
    char n_val;
    int move;
};

const std::vector<Rule> rules = {
    {'S', '0', 'S', '0', 1},
    {'S', '1', 'A', '1', 1},
    {'S', '#', 'S', '#', 1},
    {'A', '0', 'A', '0', 1},
    {'A', '1', 'S', '1', 1},
    {'A', '#', 'B', '#', -1},
    {'B', '0', 'B', '0', -1},
    {'B', '1', 'B', '1', -1},
    {'B', '#', 'C', '#', 1},
    {'C', '0', 'C', '0', 1},
    {'C', '1', 'D', '0', 0},
    {'D', '0', 'D', '0', 0}
};

void turing(std::string &in){
    char st = 'S';
    int head = 0;
    bool success = true;
    while(success){
        success = false;
        for(auto &v : rules){
            if(st == v.c_st and in[head] == v.c_val){ 
                success = true;
                st = v.n_st;
                in[head] = v.n_val;
                head += v.move;
                break;
            }
            if(st == 'D' || head < 0) return;
        }
    }
}


int main(){
    std::string input;
    std::cin >> input;
    turing(input);
    std::cout << input;
    return 0;
}
