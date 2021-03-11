#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

enum { SIZE = sizeof(unsigned short) };

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return 1;
    }
    unsigned char buf[SIZE];
    unsigned short num = 0, min = -1;
    while(read(fd, buf, sizeof(buf)) == sizeof(buf)) {
        num = (((unsigned short) buf[0] << CHAR_BIT) | buf[1]);
        if (num % 2 == 0) {
            if (num < min) {
                min = num;
            }
        }
    }
    if (min % 2 == 0) {
        printf("%hu\n", min);
    }
    close(fd);
    return 0;
}
