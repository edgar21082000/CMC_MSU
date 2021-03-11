#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int status = 0;    
    pid_t pid;
    pid = fork();
    if (!pid) {
        pid = fork();
        if (!pid) {
            printf("3 ");
        } else {
            wait(&status);
            printf("2 ");
        }
    } else {
        wait(&status);
        printf("1\n");
    }
    return 0;
}
