#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

enum
{
    BUF_SIZE = 16,
    D_LEFT = 10, // для сдвига влево цифры в десятичном числе
};

int main(void)
{
    char buf[BUF_SIZE];
    unsigned long long int tmp = 0, sum = 0;
    int f = 0; // f - flag
    int sign = 1; // sign of number
    while ((f = read(STDIN_FILENO, buf, sizeof(buf)))) {
        for (int i = 0; i < f; i++) {
            if (buf[i] == '+') {
                sign = 1;
            } else if (buf[i] == '-') {
                sign = -1;
            } else if (buf[i] >= '0' && buf[i] <= '9') {
                tmp = tmp * D_LEFT + (buf[i] - '0') * sign;
            } else if (isspace((unsigned char) buf[i])) {
                sum += tmp;
                tmp = 0;
                sign = 1;
            }
        }
    }
    printf("%lld\n", sum);
    return 0;
}
