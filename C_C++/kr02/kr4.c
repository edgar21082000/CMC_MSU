#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int pos = argc - 1;
    int p_name, status = 0;
    
    while (pos > 1) {
        while (pos > 1 && strcmp(argv[pos], argv[1])) {
            pos--;
        }

        pid_t pid;
        if ((pid = fork()) == 0) {
            p_name = pos + 1;
            execvp(argv[p_name], argv + p_name);
            _exit(1);
        }
        argv[pos] = NULL;
        pos--;

        waitpid(pid, &status, 0);
        if (!(WIFEXITED(status) && !WEXITSTATUS(status))) {
            return 1;
        }   
    }
    return 0;
}


