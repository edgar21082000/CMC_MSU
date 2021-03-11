#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

enum
{
    BAD_IDEA = 0x0bad1dea,
    BEDA = 0xbedabeda
};

char * getline2(FILE *);
int sign(long int);

int main(void)
{
    int str_sum = 0, str_num = 0, cnt = 0;
    long int cur_num;
    char *buf, *buf_cpy, *endptr;
    int ind = 0, all_space = 1, letter = 0, need_dig = 0; // флаги для контроля строки
    while ((buf = getline2(stdin))) {
        buf_cpy = buf;
        str_num++;
        str_sum = 0;
// Проверка строки на наличие буквы или только пробельных символов
        ind = 0;
        all_space = 1;
        letter = 0;
        need_dig = 0;
        while(buf[ind]) {
            if (!isspace((unsigned char) buf[ind])) {
                all_space = 0;
                if (!isdigit((unsigned char) buf[ind]) && !need_dig) {
                    letter = 1;
                    if (buf[ind] == '+' || buf[ind] == '-' ) {
                        need_dig = 1;
                        letter = 0;
                    } else {
                        break;
                    }
                } else {
                    if(isdigit((unsigned char) buf[ind])) {
                        need_dig = 0;
                    }
                    if (need_dig) {
                        break;
                    }
                }
            } else if (need_dig) {
                break;
            }
            ind++;
        }
        if (all_space) {
            str_sum = (unsigned int) str_num + BAD_IDEA;
            printf("%d\n", str_sum);
        }
        if (letter || need_dig) {
            str_sum = (unsigned int) str_num + BEDA;
            printf("%d\n", str_sum);
        }
//
        cnt = 0;
        while(!all_space && !letter && !need_dig) {
            cnt++;
            errno = 0;
            cur_num = strtol(buf, &endptr, 10);
            if (buf == endptr) { // достигли конца строки
                printf("%d\n", str_sum);
                break;
            }
            buf = endptr;
            if (errno == ERANGE) {
                cur_num = sign(cur_num) * cnt;
            }
            str_sum = (unsigned int) str_sum + cur_num;
        }
        free(buf_cpy);
    }
    return 0;
}

int sign(long int a)
{
    if (a < 0) {
        return -1;
    }
    return 1;
}

