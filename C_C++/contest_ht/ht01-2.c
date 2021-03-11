#include <stdint.h>

int32_t satsum(int32_t, int32_t);

int32_t
satsum(int32_t a, int32_t b)
{
    int32_t res = 0;
    if (!__builtin_sadd_overflow(a, b, &res)) {
        return res;
    } else {
        int32_t max = ((uint32_t) -1) >> 1; 
        int32_t min = ~max;
        if (res > 0) {
            return min;
        } else {
            return max;
        }
    }
}
