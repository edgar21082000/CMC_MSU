#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>


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
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }
    
        return 0;
    }
    
    if ((pid = fork()) < 0) {
        _exit(1);
    } else if (!pid) {
        dup2(fd[0], 0);
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        int fd2 = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, 0600);
        dup2(fd2, 2);
        close(fd2);        
    
        pid_t pid1;
        if ((pid1 = fork()) < 0) {
            _exit(1);
        } else if (!pid1) {
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
        wait(&status);
        
        pid_t pid2 = -1;
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            if ((pid2 = fork()) < 0) {
            _exit(1);
            } else if (!pid2) {
                execlp(argv[3], argv[3], NULL);
                _exit(1);
            }
        }
        
        wait(&status);
        if (pid2 != -1) {
            return (WIFEXITED(status) && !WEXITSTATUS(status));   
        }

        return 0;
    }

    if ((pid = fork()) < 0) {
        _exit(1);
    } else if (!pid) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);        

        pid_t pid1;
        if ((pid1 = fork()) < 0) {
            _exit(1);
        } else if (!pid1) {
            execlp(argv[4], argv[4], NULL);
            _exit(1);
        }
    
        return 0;
    }
    close(0);
    close(fd[0]);
    close(fd[1]);
    while(wait(NULL) != -1);
    return 0; 
}

