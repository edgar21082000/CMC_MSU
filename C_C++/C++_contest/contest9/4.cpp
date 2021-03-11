//S -> aAd
//A -> aAd | bB
//B -> bBc | c


#include <iostream>
const char * B(int rest_len){
    if(rest_len)
        std::cout<<'b'<<B(rest_len-2)<<'c';
    return "";
}


const char * A(int rest_len, int ad_len){
    if(ad_len)
        std::cout<<'a'<<A(rest_len-2, ad_len-1)<<'d';
    else
        std::cout<<'b'<<B(rest_len-2)<<'c';
    return "";
}

const char * S(int rest_len, int ad_len){
    std::cout<<'a'<<A(rest_len-2, ad_len-1)<<'d';
    return "";
}


void rec(int rest_len, int ad_len){
    if(!ad_len) return;
    std::cout<<S(rest_len, ad_len)<<std::endl;
    rec(rest_len, ad_len-1);
}

int main()
{
    int k;
    std::cin >> k;
    if(!(k%2)) rec(k, k/2 - 1);
    return 0;
}

