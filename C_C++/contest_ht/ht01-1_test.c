#include <stdio.h>
#include <stdlib.h>

extern FILE *stdin;

enum { SIZE = 128 };

char * getline2(FILE *);

int main(void)
{
    FILE *f = fopen("in.txt", "r");
    char *new = getline2(f);
    printf("%s_lol\n", new);
    return 0;
}

 
char 
*getline2(FILE *f)
{
    int lengh = 0;
    size_t buf_size = SIZE;
    char *buf = calloc(buf_size, sizeof(*buf));
    char *signal;
    int tmp;
    while(1){
        tmp = fgetc(f);
        if(tmp == EOF) {
            if(lengh == 0) {
                free(buf);
                return NULL;
            }
            return buf;
        } else {
            lengh++;
            if(lengh >= buf_size) {
                buf_size <<= 1;
                signal = realloc(buf, buf_size * sizeof(*signal));
                if(signal == NULL) {
                    free(buf);
                    return signal;
                }
                buf = signal;
            } 
            buf[lengh - 1] = tmp;
            buf[lengh] = '\0';
            if(tmp == '\n') {
                 return buf;
            }
        }
    }  
}


