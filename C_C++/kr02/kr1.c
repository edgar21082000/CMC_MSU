#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void f(int, int);

int main(int argc, char **argv)
{
    int n;
    sscanf(argv[1], "%d", &n); 
    f(0, n + 1);    
    return 0;
}

void f(int k, int n)
{
    if (!n) return;
    if(!fork()) {
        f(2 * k + 1, n - 1);
        return ;
    }
    wait(NULL);

    printf("%d\n", k);
    fflush(stdout);

    if(!fork()) {
        f(2 * k + 2, n -1);
        return;
    }
    wait(NULL);
    return;
}



