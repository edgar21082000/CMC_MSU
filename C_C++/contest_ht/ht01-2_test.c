#include <stdio.h>
#include <stdint.h>

int32_t satsum(int32_t, int32_t);

int main(void)
{
    int32_t a, b;
    while(scanf("%d %d", &a, &b)) {
        printf("%d\n", satsum(a, b));
    }
    return 0;
}


int32_t
satsum(int32_t a, int32_t b)
{
    int32_t res = 0;
    if (!__builtin_sadd_overflow(a, b, &res)) {
        return res;
    } else {
        uint32_t min = 1 << (sizeof(uint32_t) * 8 - 1);
        int32_t max = min;
        while ((max & 1) == 0) {
            max >>= 1;
        }
        max ^= min;
        if (res > 0) {
            return min;
        } else {
            return max;
        }
    }
}
