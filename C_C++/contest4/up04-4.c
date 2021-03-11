#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        return 1;
    }
    long long min, tmp, pos = 0, index = 0;
    if (read(fd, &min, sizeof(min)) != sizeof(min)) {
        close(fd);
        return 0;
    }

    while (read(fd, &tmp, sizeof(tmp)) == sizeof(tmp)) {
        index++;
        if (tmp < min) {
            min = tmp;
            pos = index;
        }
    }
    if (lseek(fd, pos * sizeof(long long), SEEK_SET) == -1) {
        return 1;
    }
    min = -(unsigned long long)min;
    if (write(fd, &min, sizeof(min)) != sizeof(min)) {
        return 1;
    }
    close(fd);
    return 0;
}
