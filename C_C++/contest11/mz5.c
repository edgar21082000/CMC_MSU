#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

volatile int cur = 0;

void handler(int s)
{
    static int i = 0;
    if (s == SIGINT) {
        i++;
        if (i > 3) {
            _exit(0);
        }
        printf("%d\n", cur);
        fflush(stdout);
    }
    if (s == SIGTERM) {
        _exit(0);
    }

}

int main(int argc, char **argv)
{
    sigaction(SIGINT, &(struct sigaction){.sa_handler=handler, .sa_flags=SA_RESTART}, NULL);
    sigaction(SIGTERM, &(struct sigaction){.sa_handler=handler, .sa_flags=SA_RESTART}, NULL);

    printf("%d\n", getpid());
    fflush(stdout);
    int low, high;
    scanf("%d", &low);
    scanf("%d", &high);
    
    for (int i = low; i < high; i++) {
        int flag = 1;    
        for (int j = 2; j*j < i; j++) {
                        
            if (i % j == 0) {
                flag = 0;
                
                break;
            }
        }
        if (flag) {
            cur = i;
        }
    }
    printf("-1\n");
    fflush(stdout);
    return 0;
}
