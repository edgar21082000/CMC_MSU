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
void bit_round2(unsigned long long *arr, int len, uint32_t *res, int r_cnt, int prec);

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
        s = getchar();
    }

    while (s_cnt++ < MDC) { // добиваем последнее число до 8 знаков
        arr[len] *= BASE_1;
    }

    while (prec > (int) IP_PREC_32) {
        res[res_cnt++] = shift_N(arr, len, LEFT_SHIFT_MLP_32);
        prec -= (int) IP_PREC_32;
    }

    int last_bits_counts = 0;
    while (prec > 0) {
        res[res_cnt] += shift_N(arr, len, LEFT_SHIFT_MLP_1) << (LEFT_SHIFT_MLP_32 - (++last_bits_counts));
        prec--;
    }

    bit_round2(arr, len, res, res_cnt, copy_prec);
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

void bit_round2(unsigned long long *arr, int len, uint32_t *res, int r_cnt, int prec)
{
    uint32_t mask = 1;
    int overflow = 0;
    if(shift_N(arr, len, LEFT_SHIFT_MLP_1) == 0) {
        return;
    }
    for (int i = 0; i <= len; i++) {
        if (arr[i] != 0) {
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
        if( (mask & res[r_cnt]) == 0) {
            return;
        }
    }
    overflow = 1;
    for(int i = r_cnt; i >= 0; i--) {
        while (mask) {
            if (overflow == 0) {
                break;
            }
            if (res[i] & mask) {
                res[i] ^= mask;
                mask <<= 1;
            } else {
                res[i] ^= mask;
                overflow = 0;
            }
        }
        mask = 1;
    }
    if (overflow) {
        printf("1 ");
    }
}



