#include <iostream>
#include <cstdint>
#include <functional>

unsigned bcr(int n,int k) 
{
	if (k>n/2) k=n-k;
	if (k==1)  throw n;
	if (k==0)  throw 1;
	// bcr(n-1,k)+bcr(n-1,k-1);
}

void calc_binom(int m, int k, std::function<void (uint64_t)> cb){
    printf("%d %d\n", m, k);
    if (k>m/2) k=m-k;
    try{
        if(k == 1) throw m;
        else if(k == 0) throw 1;
        else{
            try{
                int first, second;
                try{
                    calc_binom(m-1,k, cb);    
                } catch(int x){first = x;}
                try{
                    calc_binom(m-1,k-1, cb);
                } catch(int x){second = x;}
                //std::cout << first << " "<< second << "\n";
                throw first + second;
                
            } catch (int z){
                cb(z);
            }
        }    
    } catch(int z){
        cb(z);
    }
    
     
}

int main(){
    calc_binom(6, 3, [](uint64_t z) { std::cout << z << std::endl; });
    return 0;
}
