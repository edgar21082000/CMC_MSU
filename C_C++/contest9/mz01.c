#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int status = 0, f1, f2, f3;
    pid_t pid = fork();
    if (pid < 0) {
        exit(0);
    } else if (!pid) {
        if ((f1 = open(argv[2], O_RDONLY)) < 0) {
        exit(42);
        }
        if ((f2 = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, 0660)) < 0) {
            exit(42);
        }
        if ((f3 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0660)) < 0) {
            exit(42);
        }
        if (dup2(f1, 0) < 0) exit(42);
        if (dup2(f2, 1) < 0) exit(42);
        if (dup2(f3, 2) < 0) exit(42);
        close(f1);
        close(f2);
        close(f3);
        execlp(argv[1], argv[1], NULL);
        _exit(42);
    } else {
        wait(&status);
    }
    
    printf("%d\n", status);
    return 0;	
}
	
	
