#include <iostream>
#include <cmath>
#include <boost/date_time/gregorian/greg_date.hpp>

using namespace boost::gregorian;

int main()
{
    int y, m, d;
    date cur, prev;
    bool success = scanf("%d-%d-%d", &y, &m, &d);
    if(success) prev = date(y, m, d);
    
    long long diff = 0;
   
    while(scanf("%d-%d-%d", &y, &m, &d) == 3){
        cur = date(y, m, d);
        diff += abs((cur-prev).days());
        prev = cur;
    }
    std::cout << diff << std::endl;
    return 0;
}
