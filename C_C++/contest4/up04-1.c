#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

enum
{
    SIZE_NAME = 16,
    SMOURBLE = 100 // 1 smourble = 100 smourkopeek 
};

struct Bill
{
    char name[SIZE_NAME];
    int rate;
};

int main(int argc, char *argv[])
{
    int fd, tmp, cnt = 0;
    int rate_max = INT_MIN;
    int rate_2 = rate_max;
    struct Bill buy;

    for (int i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            break;
        }
        while (read(fd, &buy, sizeof(buy)) == sizeof(buy)) {
            tmp = buy.rate; 
            if (tmp > rate_max) {
                rate_2 = rate_max;
                rate_max = tmp;
                cnt++;
            } else if (tmp != rate_max && tmp >= rate_2) {
                rate_2 = tmp;
                cnt++;
            }
        }
        close(fd);
    }
    if (rate_max == INT_MIN || cnt < 2) { // нет второго по дороговизне товара
        return 0;
    }
    printf("%.2lf\n", ((double) rate_2) / SMOURBLE);
    return 0;
}
