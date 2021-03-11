#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    DIR *d;
    char name[PATH_MAX];
    unsigned long long sum_size = 0;
    struct stat buf; 
    struct dirent *dd;
    d = opendir(argv[1]);
    uid_t user = getuid();
    while((dd = readdir(d))) {
        if (snprintf(name, sizeof(name), "%s/%s", argv[1], dd->d_name) >= sizeof(name)) {
            closedir(d);
            return 1;
        }
        if (stat(name, &buf) >= 0) {
            if(S_ISREG(buf.st_mode) && buf.st_uid == user 
                    && isupper((unsigned char) dd->d_name[0])) {
                sum_size += buf.st_size;
            }
        }
    }
    closedir(d);
    printf("%llu\n", sum_size);
    return 0;
}
