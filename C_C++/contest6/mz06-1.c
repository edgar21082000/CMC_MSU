#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct stat buf;
    unsigned long long sum_size = 0;
    for(int i = 1; i < argc; i++) {
        if (lstat(argv[i], &buf) >= 0) {
            if (S_ISREG(buf.st_mode) && buf.st_nlink == 1) {
                sum_size += buf.st_size;
            }
        }
    }
    printf("%llu\n", sum_size);
    return 0;
}
