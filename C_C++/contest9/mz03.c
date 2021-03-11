#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int f(const char *name);

int main(int argc, char **argv)
{
    return !((f(argv[1]) || f(argv[2])) && f(argv[3]));
}

int f(const char *name)
{
    pid_t pid;
    int status = 0;
    pid = fork();
    if (pid < 0) {
        exit(0);
    } else if (!pid) {
        execlp(name, name, NULL);
        _exit(1);
    } else {
        wait(&status);
        return (WIFEXITED(status) && !WEXITSTATUS(status)); 
    }
}
