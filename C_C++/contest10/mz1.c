#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);
    pid_t pid;
    time_t t = 0;    
    if ((pid = fork()) < 0) {
        _exit(1);
    } else if (pid > 0) {
        wait(NULL);
        close(fd[1]);
        read(fd[0], &t, sizeof(t));
        close(fd[0]);
        struct tm *tm = localtime(&t);
        printf("Y:%d\n", tm->tm_year + 1900);
        fflush(stdout);
        return 0;
    } else {
        if ((pid = fork()) < 0) {
            _exit(1);
        } else if (pid > 0) {
            wait(NULL);
            close(fd[1]);
            read(fd[0], &t, sizeof(t));
            close(fd[0]);
            struct tm *tm = localtime(&t);
            printf("M:%02d\n", tm->tm_mon + 1);
            fflush(stdout);
            return 0;
        } else {
            if ((pid = fork()) < 0) {
            _exit(1);
            } else if (pid > 0) {
                wait(NULL);
                close(fd[1]);
                read(fd[0], &t, sizeof(t));
                close(fd[0]);
                struct tm *tm = localtime(&t);
                printf("D:%02d\n", tm->tm_mday);
                fflush(stdout);
                return 0;
            } else {
                close(fd[0]);
                time_t cur_t = time(0);
                for (int i = 0; i < 3; i++) {
                    write(fd[1], &cur_t, sizeof(cur_t));
                }
                close(fd[1]);
                return 0;
            }
        }
    }
}



