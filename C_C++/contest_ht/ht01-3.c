#include <stdio.h>

enum { MANT_LEN = 23 };

int u_to_float(unsigned int);

int main(void)
{
    unsigned int num = 0;
    while(scanf("%u", &num) > 0) {
        printf("%d\n", u_to_float(num));
    }
    return 0;
}

int
u_to_float(unsigned int a)
{
    int f = 0, first_1_bit = 0;
    while (a > 1) {
        if (a & 1) {
            first_1_bit = 1;
        }
        if (first_1_bit == 1) {
            f++;
        }
        a >>= 1;
    }
    return f <= MANT_LEN;
}
