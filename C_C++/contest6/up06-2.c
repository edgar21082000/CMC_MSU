#include <stdio.h>
#include <time.h>
#include <string.h>

enum
{
    YEAR_SEC = 31104000,
    MON_SEC = 2592000,
    DAY_SEC = 86400,
    BARON_Y_BRTH = 1925,
    BARON_M_BRTH = 10,
    BARON_D_BRTH = 7,
    CORRECT_Y = -1900,
    CORRECT_M = -1,
};

int main(void)
{
    long long brth, dif, cur;
    struct tm dat;
    memset(&dat, 0, sizeof(dat));
    
    dat.tm_year = BARON_Y_BRTH + CORRECT_Y;
    dat.tm_mon = BARON_M_BRTH + CORRECT_M;
    dat.tm_mday = BARON_D_BRTH;
    dat.tm_isdst = 1;
    brth = mktime(&dat);
    memset(&dat, 0, sizeof(dat));    

    while (scanf("%d%d%d", &(dat.tm_year), &(dat.tm_mon), &(dat.tm_mday)) > 0) {
        dat.tm_year += CORRECT_Y;
        dat.tm_mon += CORRECT_M;
        dat.tm_isdst = -1;
        cur = mktime(&dat);
        memset(&dat, 0, sizeof(dat));
        dif = cur - brth;
        printf("%lld ", dif / YEAR_SEC + 1);
        dif %= YEAR_SEC; 
        printf("%lld ", dif / MON_SEC + 1);
        dif %= MON_SEC;
        printf("%lld\n", dif / DAY_SEC + 1);
    }
    return 0;
}
