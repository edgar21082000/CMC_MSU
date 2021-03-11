#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

enum
{
    SYM_CNT = 8,
    SON_CNT = 3
};

void read_num(int);

int main(int argc, char *argv[])
{
    int status = 0;
    pid_t pid;
    for (int i = 0; i < SON_CNT; i++) {
        pid = fork();
        if (!pid) {
            read_num(i);
            return 0;
        }
    }
    while (wait(&status) > 0) {
        status = 0;
    }
    return 0;
}

void read_num(int i)
{
    char num[SYM_CNT];  
    read(STDIN_FILENO, num, sizeof(num));
    int sq;
    sscanf(num, "%d", &sq);
    sq *= sq;
    printf("%d %d\n", i + 1, sq);
}


