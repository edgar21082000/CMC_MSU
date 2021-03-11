#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

void everyone_dies(pid_t *, int);

int main(int argc, char **argv)
{
    pid_t *pid_arr = calloc(argc, sizeof(pid_t)) ;    

    int fd[2];
    for (int i = 1; i < argc - 1; i++) {
        if (pipe(fd) < 0) {
            everyone_dies(pid_arr, i);
            _exit(1);
        }
        
        if ((pid_arr[i] = fork()) < 0) {
            everyone_dies(pid_arr, i);
            _exit(1);
        } else if (!pid_arr[i]) {
            free(pid_arr);
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            execlp(argv[i], argv[i], NULL);
            _exit(1);    
        } else {
            if (dup2(fd[0], 0) < 0) {
                everyone_dies(pid_arr, i + 1);
                _exit(1);            
            }

            if (close(fd[0]) < 0) {
                everyone_dies(pid_arr, i + 1);
                _exit(1);
            }
            
            if (close(fd[1]) < 0) {
                everyone_dies(pid_arr, i + 1);
                _exit(1);
            }
        }    
    }

    if ((pid_arr[argc-1] = fork()) < 0) {
        everyone_dies(pid_arr, argc-1);
        _exit(1);
    } else if (!pid_arr[argc-1]) {
        free(pid_arr);
        execlp(argv[argc-1], argv[argc-1], NULL);
        _exit(1);
    }

    close(0);
    close(1);
 
    while(wait(NULL) != -1);
    free(pid_arr);
    return 0;
}

void everyone_dies(pid_t *arr, int n)
{
    for (int i = 1; i < n; i++) {
        kill(arr[i], SIGKILL);
    }
    while(wait(NULL) != -1);
    free(arr);
    return;
}
