#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(void)
{
    int n, status = 0, first = 0;
    pid_t pid;
    while(scanf("%d", &n) == 1) {
        pid = fork();
        if (pid > 0) {
            wait(&status);
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                printf("%d\n", n);
                return 0;
            } else if (first == 0){
                printf("-1\n");
                return 0;
            } else {
                exit(1);
            }
        } else if (pid < 0) {
            exit(1);
        } else {
            first = 1;
        }
    }   
    return 0;
}
