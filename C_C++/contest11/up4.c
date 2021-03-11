#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int pid1, pid2, fd[2], n;
volatile int flag = 0;

typedef struct P_inf
{
    pid_t pid;
    int num;
} P_inf;

void handler(int s)
{
    flag = 1;
}

void ping_pong(P_inf a, int s)
{
    FILE *in = fdopen(fd[0], "r");
    FILE *out = fdopen(fd[1], "w");

    int pid, x;
    if (a.pid == -1) {
        fscanf(in, "%d", &pid);
    }  else {
        pid = a.pid;
    }

    while(1) {
        while (!flag) {
        //printf("%d\n", a.num);
            pause();
        }
        flag = 0;
        fscanf(in, "%d", &x);
        if (x >= n) break; // for finish second processes
        printf("%d %d\n", a.num, x);
        fflush(stdout);
        if (++x >= n) {  
            fprintf(out, "%d\n", x);
            kill(pid, s);
            break;
        }
        fprintf(out, "%d\n", x); 
        fflush(out);
        kill(pid, s);
    }
    fclose(in);
    fclose(out);
    close(fd[0]);
    close(fd[1]);
    return;
}



int main(int argc, char *argv[])
{
    sigaction(SIGUSR1, &(struct sigaction){.sa_handler=handler, .sa_flags=SA_RESTART}, NULL);

    sscanf(argv[1], "%d", &n);
    if (n <= 1) {
        printf("Done\n");
        return 0;
    }
   
    pipe(fd);

    if(!(pid1 = fork())) {
        P_inf proc_info;
        proc_info.pid = -1;
        proc_info.num = 1;
        ping_pong(proc_info, SIGUSR1);
        return 0;
    }
    if(!(pid2 = fork())) {
        P_inf proc_info;
        proc_info.pid = pid1;
        proc_info.num = 2;     
        ping_pong(proc_info, SIGUSR1);
        return 0;
    }


    FILE *out = fdopen(fd[1], "w");
    close(fd[0]);
    fprintf(out, "%d\n1\n", pid2);
    fflush(out);
    fclose(out);
    close(fd[1]);
    kill(pid1, SIGUSR1);

    while(wait(NULL) != -1);
    printf("Done\n");
    return 0;
}
