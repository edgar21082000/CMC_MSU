#include <iostream>
#include <algorithm>
#include <vector>

void process(const std::vector<int> &v1, std::vector<int> &v2)
{
    if (!v1.size() || !v2.size()) return;
    
    auto v1_c = v1;
    std::sort(v1_c.begin(), v1_c.end());
    auto last = std::unique(v1_c.begin(), v1_c.end());
    v1_c.erase(last, v1_c.end());
    
//    for(auto i : v1_c)
//        std::cout <<i<<' ';
//    printf("\n");
    
    int del = 0;
    auto l = v2.begin(), r = v2.begin();
    auto start = r;
    
    auto del_elem = v1_c.begin();
    while(*del_elem < 0) del_elem++;
    
    while(r < v2.end()){
        if(r - start == *del_elem){
            del_elem++;
            del++;
        } else {
            std::swap(*l, *r);
            l++;
        }
        r++;
    }
    
    v2.erase(v2.end() - del, v2.end());
    v1_c.clear();
}

int main(void)
{
    const std::vector<int> del_list = {19};
    std::vector<int> s = {10, 11, 12, 13, 14};
    
    for(size_t i = 0; i < s.size(); i++)
        printf("%d ", s[i]);
    printf("\n");
    
    process(del_list, s);
    
    for(size_t i = 0; i < s.size(); i++)
        printf("%d ", s[i]);
}
