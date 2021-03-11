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
    int status = 0;

    if ((pid = fork()) < 0) {
        _exit(1);
    } else if (!pid) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        
        pid_t pid1;
        if ((pid1 = fork()) < 0) {
            _exit(1);
        } else if (!pid1) {
            int fd1 = open(argv[4], O_RDONLY);
            dup2(fd1, 0);
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }
        wait(&status);
        
        pid_t pid2 = -1;
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            if ((pid2 = fork()) < 0) {
            _exit(1);
            } else if (!pid2) {
                execlp(argv[2], argv[2], NULL);
                _exit(1);
            }
        }
        
        wait(&status);
        if (pid2 != -1) {
            return !(WIFEXITED(status) && !WEXITSTATUS(status));   
        }
    
        return 0;
    }
    
    if ((pid = fork()) < 0) {
        _exit(1);
    } else if (!pid) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        int fd2 = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0666);
        dup2(fd2, 1);
        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    while(wait(NULL) != -1);
    return 0; 
}

