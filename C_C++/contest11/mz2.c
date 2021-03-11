#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

volatile int f = 0, r = 0;

void handler(int s)
{
    if (s == SIGINT) {
        f = 0;
    }
    if (s == SIGQUIT) {
        f = 1;
    }
}

int main(int argc, char **argv)
{
    sigaction(SIGINT, &(struct sigaction){.sa_handler=handler, .sa_flags=SA_RESTART}, NULL);
    sigaction(SIGQUIT, &(struct sigaction){.sa_handler=handler, .sa_flags=SA_RESTART}, NULL);
    
    printf("%d\n", getpid());
    fflush(stdout);
    
    int ans = 0, cur;
    while(scanf("%d", &cur) == 1) {
        if (f == 0) {
            ans = (unsigned int)ans + cur; 
        }
        if (f == 1) {
            ans = (unsigned int)ans * cur;
        }
        printf("%d\n", ans);
        fflush(stdout);
    }
    return 0;
}


