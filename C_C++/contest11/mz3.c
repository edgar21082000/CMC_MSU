#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <limits.h>

int main(int argc, char **argv)
{
    int n, res = 0, status;
    sscanf(argv[1], "%d", &n);
    for (int i = 2; i <= n+1 && i < argc; i++) {
        if(!fork()) {
            char *name = calloc(PATH_MAX, sizeof(char));
            FILE *f = fopen(argv[i], "r");
            fgets(name, PATH_MAX, f);
            fclose(f);
            name[strlen(name) - 1] = '\0';    
            execlp(name, name, NULL);
            _exit(1);
        }
    }
    for (int i = 2; i <= n+1 && i < argc; i++){
        wait(&status);
        res += (WIFEXITED(status) && !WEXITSTATUS(status));
    }
    
    for (int i = n+2; i < argc; i++) {
        if(!fork()) {
            char *name = NULL;
            int size = 0;
            FILE *f = fopen(argv[i], "r");
            getline(&name, &size, f);
            fclose(f);
            name[strlen(name) - 1] = '\0';    
            execlp(name, name, NULL);
            _exit(1);
        }
        wait(&status);
        res += (WIFEXITED(status) && !WEXITSTATUS(status));
    }
    printf("%d\n", res);
}
