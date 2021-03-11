#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

enum
{
    BUF_SIZE = 16,
    D_LEFT = 10, // для сдвига влево цифры в десятичном числе
    STDIN = 0,
};

int main(void)
{
    char buf[BUF_SIZE];
    long long int tmp = 0, sum = 0;
    int f = 0; // f - flag
    int sign = 1; // sign of number
    while ((f = read((int) STDIN, buf, BUF_SIZE))) {
        for (int i = 0; i < f; i++) {
printf("symbol - '%c'\n", buf[i]);
printf("tmp = %lld\n", tmp);
printf("sum = %lld\n", sum);
            if (buf[i] == '+') {
printf("____if0\n");
                sign = 1;
                continue;
            } else if (buf[i] == '-') {
printf("____if1\n");
                sign = -1;
                continue;
            } else if (buf[i] >= '0' && buf[i] <= '9') {
printf("____if2\n");
                tmp = (unsigned long long int) tmp
                        * (unsigned long long int) D_LEFT
                                + (unsigned long long int) (buf[i] - '0')
                                        * sign;
                continue;
            } else if (isspace((int) buf[i])) {
printf("____if3\n");
                sum = (unsigned long long int) sum
                        + (unsigned long long int) tmp;
                tmp = 0;
                sign = 1;
            }
        }
    }
    printf("%lld\n", sum);
    return 0;
}

