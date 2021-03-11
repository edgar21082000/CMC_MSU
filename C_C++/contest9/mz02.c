#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int mysys(const char *str)
{
    int status = 0;
    pid_t pid = fork();
    if (pid < 0) {
        return -1;   
    } else if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } else {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            return WTERMSIG(status) + 128;
        }
        return WEXITSTATUS(status);
    }
}
