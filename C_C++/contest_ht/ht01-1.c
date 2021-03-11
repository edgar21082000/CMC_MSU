#include <stdio.h>
#include <stdlib.h>

enum { START_SIZE = 16 };

char * getline2(FILE *);

char * getline2(FILE *f)
{
    int s;
    int ind = 0;
    char *buf = NULL, *re_buf = NULL;
    size_t size = (size_t) START_SIZE;
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

