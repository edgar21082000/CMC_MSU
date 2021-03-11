#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);
    pid_t pid;
    
    if ((pid = fork()) < 0) {
        _exit(1);
    } else if (pid > 0) {
        close(fd[0]);
        int n = 0;
        while (scanf("%d", &n) == 1) {
            write(fd[1], &n, sizeof(n));
        }
        close(fd[1]);
        wait(NULL);
        return 0;
    } else {
        close(fd[1]);
        if ((pid = fork()) < 0) {
            _exit(1);
        } else if (pid > 0) {
            close(fd[1]);
            wait(NULL);
        } else {
            int n;
            long long sum = 0;
            while ((read(fd[0], &n, sizeof(n)) == sizeof(n))) {
                sum += n;
            }
            close(fd[0]);
            printf("%lld\n", sum);
            return 0;
        }
        close(fd[0]);
        wait(NULL);
        return 0;
    }
}
