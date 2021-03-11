#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum
{
    ROUND = 10000,
    OHP = 100, // one hundred percent
};

int main(int argc, char *argv[])
{
    double rate = 0, percnt = 0;
    sscanf(argv[1], "%lf", &rate);
    for (int i = 2; i < argc; i++) {
        sscanf(argv[i], "%lf", &percnt);
        rate += rate * percnt / (double) OHP;
        rate *= (double) ROUND;
        rate = round(rate);
        rate /= (double) ROUND;
    }
    printf("%.4lf\n", rate);
    return 0;
}
