#include <stdio.h>
#include <inttypes.h>


int32_t n_sign(int32_t, int32_t);

int main(void)
{
    uint32_t n, w;
    scanf("%" SCNo32 "%" SCNo32, &n, &w);
    uint32_t CNT = 1 << n; // степень 2
    for (uint32_t i = 0; i < CNT; i++) {
        printf("|" "%*"  PRIo32 , (int) w, i);
        printf("|" "%*"  PRIu32 , (int) w, i);
        printf("|" "%*"  PRId32 "|\n", (int) w, n_sign(i, n) * (i & ~(1 << (n-1))));
            
    }
    return 0;     
}

int32_t n_sign(int32_t a, int32_t n)
{
    if (!(a & (1 << (n-1)))) {
        return 1;
    }
    return -1;
}

