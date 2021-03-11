#include <stdio.h>

int main(int argc, char *argv[])
{
    long long int pos_sum = 0, neg_sum = 0;
    int tmp = 0;
    for (int i = 1; i < argc; i++) {
        sscanf(argv[i], "%d", &tmp);
        if (tmp >= 0) {
            pos_sum += tmp;
        } else {
            neg_sum += tmp;
        }
    }
    printf("%lld\n%lld\n", pos_sum, neg_sum);
    return 0;
}
