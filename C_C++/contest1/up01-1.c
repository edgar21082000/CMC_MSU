#include <stdio.h>
#include <stdlib.h>

int sign_a(int); // данная ф-ция будет возвращать знак а; 

int main(void)
{
    int a, b, c, dif, res; 
    scanf("%d%d", &a, &b);
    c = a / b * b;
    dif = abs(a-c);
    b *= sign_a(a);
    if (!__builtin_sadd_overflow(c, b, &res) && dif != 0) {
        c = res;
        if (a > 0 && abs(a - c) > dif) {
            c -= b;
        }
        if (a < 0 && abs(a - c) >= dif) {
            c -= b;
        }
    }
    printf("%d\n", c);
    return 0;
}

int
sign_a(int a)
{
    if (a>=0) {
        return 1;
    }
    return -1;
}

