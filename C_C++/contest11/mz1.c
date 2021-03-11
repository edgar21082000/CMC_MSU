#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

enum
{
    STOP = 5
};

void handler(int s)
{
    static int i = 0;
    if (i == STOP){
        exit(0);
    }
    printf("%d\n", i);
    fflush(stdout);
    i++;   
}

int main(int argc, char **argv)
{
    sigaction(SIGHUP, &(struct sigaction){.sa_handler=handler, .sa_flags=SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    for(;;) pause();
    return 0;
}
