#include <iostream>

int main(){
    int cnt;
    std::cin>>cnt;
    
    Holder *arr = new Holder[cnt];

    for(int i=0; i < cnt/2; i++)
        arr[cnt-i-1].swap(arr[i]);
        
    
    delete []arr;
    return 0;
}
