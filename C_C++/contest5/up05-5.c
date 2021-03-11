#include <stdio.h>
#include <string.h>
#include <time.h>

enum
{
    CORRECT_Y = -1900,
    CORRECT_M = -1,
    N_ARG = 6,
};

int read_time(FILE *fd, struct tm *t);
time_t init_time(struct tm *t);


int main(int argc, char *argv[])
{
    FILE *fd = fopen(argv[1], "r");
    if (!fd) {
        return 1;
    }

    time_t cur = 0, prev = 0;
    struct tm t;
    memset(&t, 0, sizeof(t));
    
    
    read_time(fd, &t);
    prev = init_time(&t);

    while (read_time(fd, &t)) {
        cur = init_time(&t);
        printf("%ld\n", cur - prev);
        prev = cur;     
    }
    fclose(fd);
    return 0;
}

int read_time(FILE *fd, struct tm *t)
{
    return (fscanf(fd, "%d/%d/%d%d:%d:%d", &(t->tm_year), &(t->tm_mon), &(t->tm_mday), 
            &(t->tm_hour), &(t->tm_min), &(t->tm_sec)) == N_ARG);
}

time_t init_time(struct tm *t)
{
    t->tm_isdst = -1;
    t->tm_year += CORRECT_Y;
    t->tm_mon += CORRECT_M;
    return mktime(t);
}
