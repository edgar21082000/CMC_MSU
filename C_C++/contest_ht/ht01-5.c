#include <stdio.h>
#include <ctype.h>
#include <stdint.h>


enum
{
    MAX_ARR_SIZE = 6250, // = 50000 / sizeof(long long)
    MDC = 8, // макс. кол-во десятичных цифр в записи числа
    MAX_ANS_SIZE = 5000, // верхняя оценка 150000 / 32
    LEFT_SHIFT_MLP_32 = 32, // умножание на 2^32, необходимое для  вывода 32бит
    LEFT_SHIFT_MLP_1 = 1, // аналогично пред.
    BASE_1 = 10,
    BASE_8 = 100000000, // 10^8 для получения целоqй части и остатка в преобразованных после сдвига чисел см. MDC
    IP_PREC_32 = 32, // (integer part) Составляем по 32бита, до момента, пока потребуется записать кол-во бит < 32
};

uint32_t shift_N(unsigned long long *, int, int);
//void bin_round(uint32_t *, int, int, unsigned long long *, int);
//int check_long(unsigned long long *, int);
//void plus_1(uint32_t *, int, int);
void bit_round2(unsigned long long *arr, int len, uint32_t *res, int r_cnt, int prec);

int
myround (unsigned long long *number, int N, uint32_t *frac, int M, int prec);

int main(void)
{
    int prec;
    scanf("%d", &prec);
    int copy_prec = prec;
    uint32_t res[MAX_ANS_SIZE] = {};
    int res_cnt = 0;
    unsigned long long arr[MAX_ARR_SIZE] = {};
    int len = 0, s, s_cnt = 0;
    s = getchar();
    while(isspace((unsigned char) s)) {
        s = getchar();
    }     
    
    while(isdigit((unsigned char) s) && s != EOF) { // записываем числа из строки по 8цифр в элементы массива
        arr[len] = arr[len] * BASE_1 + (s - '0');
        s_cnt++;
        if (s_cnt == MDC) {
            s_cnt = 0;
            len++;
        }
//printf("s = %c | arr[%d] = %08llx\n", s, len, arr[len]);
        s = getchar();
    }
//printf("\n-------------------------------------\n");

    while (s_cnt++ < MDC) { // добиваем последнее число до 8 знаков
        arr[len] *= BASE_1;
    }

    while (prec > (int) IP_PREC_32) {
//for(int g=0; g<=len; g++) printf("%08llx ", arr[g]);
//printf("\n");
        res[res_cnt++] = shift_N(arr, len, LEFT_SHIFT_MLP_32);
        prec -= (int) IP_PREC_32;
    }

    int last_bits_counts = 0;
    while (prec > 0) {
        res[res_cnt] += shift_N(arr, len, LEFT_SHIFT_MLP_1) << (LEFT_SHIFT_MLP_32 - (++last_bits_counts));
        prec--;
    }

/*  for (int i = 0; i <= res_cnt; i++) {
        printf("| %08x | ", res[i]);
    }
    printf("\n");
*/

//    bin_round(res, res_cnt, last_bits_counts, arr, len);
    int k = myround(arr, len + 1, res, res_cnt + 1, copy_prec);
    if (k) printf("1 ");
//    bit_round2(arr, len + 1, res, res_cnt + 1, copy_prec);
    for (int i = 0; i <= res_cnt; i++) {
        printf("%08x ", res[i]);
    }
    printf("\n");

    return 0;
}

uint32_t shift_N(unsigned long long *arr, int len, int shift_count)
{
    uint32_t rod = 0;
    for (int i = len; i >= 0; i--) {
        arr[i] <<= shift_count;
        arr[i] += rod;
        rod = arr[i] / BASE_8;
        arr[i] %= BASE_8;
    }
    return rod;
}

/*void bit_round2(unsigned long long *arr, int len, uint32_t *res, int r_cnt, int prec)
{
    uint32_t mask = 1;
    int i, overflow = 1;
    if(shift_N(arr, len, LEFT_SHIFT_MLP_1) == 0) {
printf("here1\n");
        return;
    }
    i = 0;
    while(i++ < len) {
        if (arr[i]) {
printf("here2\n");
            overflow = 1;
            break;
        }
    }
    int shift = IP_PREC_32 - prec % 32;
    if (shift == 0) {
        mask = 0;
    } else {
        mask <<= shift;
    }

    if (overflow == 0) {
printf("here3\n");
        if( (mask & res[r_cnt - 1]) == 0) {
printf("here4\n");            
            return;
        }
    }
    overflow = 1;
    i = r_cnt;
    while(--i >= 0) {
        while (mask) {
            if (overflow == 0) {
printf("here5\n");
                break;
            }
            if (res[i] & mask) {
printf("here_NO\n");
                res[i] ^= mask;
                mask <<= 1;
            } else {
                res[i] ^= mask;
                overflow = 0;
printf("here6\n");
            }
        }
        mask = 1;
    }
    if (overflow) {
        printf("1 ");
    }
}
*/




/*void bin_round(uint32_t *res, int r_cnt, int lbc, unsigned long long *arr, int len)
{
//for(int g=0; g<=len; g++) printf("<%llx >", arr[g]);
    uint32_t prec_1 = shift_N(arr, len, LEFT_SHIFT_MLP_1); // возвращаем след. бит на проверку
//printf("<%d>\n", prec_1);
    if (prec_1 == 0) {
        return ;
    } else {
        int key = check_long(arr, len);
//printf("-|%d|-\n", key);        
        if (key) {
            plus_1(res, r_cnt, lbc);
        } else if ( (res[r_cnt] & (1 << (LEFT_SHIFT_MLP_32 - lbc))) ) { // бит prec == 1
            plus_1(res, r_cnt, lbc);
        } else {
            return;
        }
    }
}

int check_long(unsigned long long *arr, int len)
{
    for (int i = 0; i < len; i++) {
        if (arr[i]) {
            return 1;
        }
    }
    return 0;
}

void plus_1(uint32_t *res, int r_cnt, int lbc)
{
    int sh = LEFT_SHIFT_MLP_32 - lbc;
    uint32_t mask = 1 << sh;
    for (int i = r_cnt; i >= 0; i--) {
        while(mask){
            res[r_cnt] ^= mask;
            if ((res[r_cnt] & mask)) { // если xor результировал в 1
                return;
            } else {
                mask <<= 1;
            }
        }
        mask = 1;
    }
    if (res[0] == 0) {
        printf("1 ");
    }
}*/

int
myround (unsigned long long *number, int N, uint32_t *frac, int M, int prec)
{
    uint32_t mask = 1;
    int i, f = 0;
    if (!shift_N(number, N, LEFT_SHIFT_MLP_1)) {
        return 0;
    }
    for (i = 0; i < N; i++) {
        if (number[i] != 0) {
            f = 1;
            break;
        }
    }
    if (!(IP_PREC_32 - prec % 32)) {
        mask = 0;
    } else {
        mask <<= IP_PREC_32 - prec % 32;
    }
    if (!f) {
        if (!(mask & frac[M - 1])){
            return 0;
        }
    }
    f = 1;
    for (i = M - 1; i >= 0; i--) {
        while (mask) {
            if (!f) {
                break;
            }
            if (frac[i] & mask) {
                frac[i] ^= mask;
                mask <<= 1;
            } else {
                frac[i] ^= mask;
                f = 0;
            }
        }
        mask = 1;
    }
    return f;
}
