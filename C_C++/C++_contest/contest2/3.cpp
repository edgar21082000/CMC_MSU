#include <string>
#include <vector>
#include <map>

namespace numbers{
    
    std::map <std::string, void(*)(complex_stack &)> mymap = 
    {
        { "+", [] (complex_stack &st) {
            complex tmp = +st;
            st = ~st;
            tmp += +st;
            st = ~st;
            st = st << tmp;         
        } },
        
        { "-", [] (complex_stack &st) {
            complex tmp = +st;
            st = ~st;
            tmp = +st - tmp;
            st = ~st;
            st = st << tmp;         
        } },
        
        { "*", [] (complex_stack &st) {
            complex tmp = +st;
            st = ~st;
            tmp = +st * tmp;
            st = ~st;
            st = st << tmp;         
        } },
        
        { "/", [] (complex_stack &st) {
            complex tmp = +st;
            st = ~st;
            tmp = +st / tmp;
            st = ~st;
            st = st << tmp;         
        } },
        
        { "!", [] (complex_stack &st) {
            st = st << +st;
        } },
        
        { ";", [] (complex_stack &st) {
            st = ~st;  
        } },
        
        { "~", [] (complex_stack &st) {
            complex tmp = +st;
            tmp = ~tmp;
            st = ~st;
            st = st << tmp;    
        } },
        
        { "#", [] (complex_stack &st) {
            complex tmp = +st;
            tmp = -tmp;
            st = ~st;
            st = st << tmp;        
        } }
    };
    
    complex eval(const std::vector<std::string> &args, const complex &z)
    {
        complex_stack st;
        int argc = args.size();
        for (int i = 0; i < argc; i++){
            if(mymap.find(args[i]) != mymap.end()){
                mymap[args[i]](st);
            } else if (args[i] == "z") {
                st = st << z;
            } else {
                st = st << complex(args[i]);
            }
        }
        return +st;
    }
    
}
