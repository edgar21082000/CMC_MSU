#include <iostream>
#include <iomanip>
#include <cmath>

int main(){
    double sum = 0., disp = 0., x = 0.;
    int cnt = 0;
    
    while(std::cin>>x){
        sum+=x;
        cnt++;
        disp += x*x;
    }
    
    double sn = sum / cnt;
    double dn = (disp - 2*sn*sum + sn*sn*cnt)/cnt;
    dn = sqrt(dn);
    
    std::cout<<std::setprecision(10)<<sn<<"\n"<<std::setprecision(10)<<dn<<std::endl;
    return 0;
}
