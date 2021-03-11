#include <stdio.h>

int main(void) {
    unsigned int n,m;
    scanf("%d",&n);
    m = 0;
    while (n > 0) {
        m = m*10 + n%10;
        n = n/10;
        printf("%d %d\n", m, n); 
    }
    printf("%d\n",m);    
}
