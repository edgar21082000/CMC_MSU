#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

enum
{
    START_SIZE = 16,
    ND = 10, // кол-во цифр
    BUF_SIZE = 1024
};

char * getline2_mod(FILE *f);
void print(unsigned long long *);

int main(void)
{
    unsigned long long  ans[ND] = {};
    char *name = getline2_mod(stdin);
    int fd = open(name, O_RDONLY);
    if (fd < 0) {
        print(ans);
        return 0;
    }
    char buf[BUF_SIZE];
    int nr = 0;
    while((nr = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < nr; i++) {
            if (buf[i] >= '0' && buf[i] <= '9') {
                ans[buf[i] - '0']++;
            }
        }
    }
    print(ans);
    free(name);
    close(fd);
    return 0;
}

void
print(unsigned long long *arr)
{
    for (int i = 0; i < ND; i++) {
        printf("%d %lld\n", i, arr[i]);
    }
}


char *
getline2_mod(FILE *f) // mod - don't save '\n'
{
    int s;
    int ind = 0;
    char *buf = NULL, *re_buf = NULL;
    size_t size = (size_t) START_SIZE;
    buf = calloc(size, sizeof(*buf));
    if (!buf) {
        return NULL;
    }
    while ((s = getc(f)) != EOF && s != '\n' && s != '\r') {
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
    }
    if (!ind) {
        free(buf);
        return NULL;
    }
    return buf;
}

