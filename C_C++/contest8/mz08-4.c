#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int N, status = 0;
    scanf("%d", &N);
    pid_t pid = 0;
    for(int i = 1; i <= N; i++) {
        if (i < N) {
            printf("%d ", i);
            fflush(stdout);
            pid = fork();    
            if (pid) {
                wait(&status);
                return 0;
            }
        } else {
            printf("%d\n", i);
        }
   
    }
    return 0;
}
