#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

enum { NB = sizeof(unsigned short) }; // кол-во байт в типе unsigned short

int main(int argc, char *argv[])
{
    int fd = creat(argv[1], 0600);
    unsigned short tmp;
    unsigned char bytes[NB];
    while (scanf("%hu", &tmp) > 0) {
        bytes[0] = (unsigned char) (tmp >> CHAR_BIT);
        bytes[1] = (unsigned char) tmp;
        write(fd, bytes, sizeof(bytes));
    }
    close(fd);
    return 0;
}
