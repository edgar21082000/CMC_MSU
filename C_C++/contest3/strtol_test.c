#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

char * getline2(FILE *);

int main(void)
{

    FILE *f = fopen("in.txt", "r");
    char *buf, *endptr;
    long int cur, a;
    while(buf = getline2(f)) {
        printf("<%s>\n", buf);
        while(1) {
            errno = 0;
printf("<%c>\n", *(buf+1));
            cur = strtol(buf, &endptr, 10);
printf("<%c>\n", *(buf+1));            
            if (buf == endptr) {
                printf("cur = %ld | err = %d\n", cur, errno);            
                break;
            }
            buf = endptr;
            printf("ERRNO = %d | pause: ", errno);
            scanf("%ld", &a);
            if (errno) {
                if (errno == ERANGE) printf("<large> __");
                if (errno == EINVAL) printf("<no digits> __");            
            }
            printf("cur = %ld\n", cur);
        }
    }
    return 0;     
}

char * getline2(FILE *f)
{
    int s;
    int ind = 0;
    char *buf = NULL, *re_buf = NULL;
    size_t size = (size_t) 16;
    buf = calloc(size, sizeof(*buf));
    if (!buf) {
        return NULL;
    }
    while ((s = getc(f)) != EOF) {
        if (ind == size - 1) {
            size <<= 1;
            re_buf = realloc(buf, size * sizeof(buf[0]));
            if (!re_buf) {
                free(buf);
                return NULL;
            }
            buf = re_buf;
        }
        buf[ind] = s;
        buf[ind + 1] = '\0';
        ind++;
        if (s == '\n') {
            break;
        }
    }
    if (!ind) {
        free(buf);
        return NULL;
    }
    return buf;
}

