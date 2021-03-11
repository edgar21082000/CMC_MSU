#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

unsigned long long hash_function(unsigned long long);

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0660);
    if (fd < 0) {
        return 0;
    }
    unsigned long long h;
    long long count;
    sscanf(argv[2], "%llx", &h);
    sscanf(argv[3], "%lld", &count);

    long input_file_end = lseek(fd, 0, SEEK_END);
    if (input_file_end == -1) {
        return 1;
    }
    for (long long i = count - 1; i >= 0; i--) {
        if (lseek(fd, input_file_end + i * sizeof(h), SEEK_SET) == -1) {
            return 1;
        }
        if (write(fd, &h, sizeof(h)) != sizeof(h)) {
            return 1;
        }
        h = hash_function(h);
    }
    close(fd);
    return 0;
}
