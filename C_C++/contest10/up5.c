#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

void ping_pong(int *, int, int);

int main(int argc, char **argv)
{
    int N;
    sscanf(argv[1], "%d", &N);
    if (N <= 1) {
        printf("Done\n");
        return 0;
    }

    //int fd1[2], fd2[2];
    //pipe(fd1);
    //pipe(fd2);   
    int fd[2]; pipe(fd);
    
    if (!fork()) {   
        /*ping_pong(fd2[0], fd1[1], 1, N);
        close(fd2[1]);
        close(fd1[0]);
        
        
        close(fd2[0]);
        close(fd1[1]);
        */
        ping_pong(fd, 1, N);
        close(fd[0]);
        close(fd[1]);
        return 0;
    }
    
    if (!fork()) {      
        /*ping_pong(fd1[0], fd2[1], 2, N);
        close(fd1[1]);
        close(fd2[0]);
        
        close(fd1[0]);
        close(fd2[1]);
        */
        ping_pong(fd, 2, N);
        close(fd[0]);
        close(fd[1]);
        
        return 0;
    }

    /*FILE *wr = fdopen(fd2[1], "w");
    fprintf(wr, "%d ", 0);
    fflush(wr);
    fclose(wr);
    
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    */
    int cmd[2];
    cmd[0] = 1;
    cmd[1] = 2;
    write(fd[1], cmd, 8);
    
    while(wait(NULL) != -1);
    printf("Done\n");
    return 0;
}

void ping_pong(int *fd, int proc, int N)
{
    //FILE *rd = fdopen(fdin, "r");
    //FILE *wr = fdopen(fdout, "w");
    int cmd[2];
    while (read(fd[0], cmd, 8)) {
        if(cmd[1] == proc){
            write(fd[1], cmd, 8);
            continue;
        }
        if (cmd[0] == N) {
            if(cmd[1] == 1) cmd[1] = 2;
            else cmd[1] = 1;
            write(fd[1], cmd, 8);
            break;
        }
        printf("%d %d\n", proc, cmd[0]);
        fflush(stdout);
        cmd[0]++;
        if(cmd[1] == 1) cmd[1] = 2;
        else cmd[1] = 1;
        write(fd[1], cmd, 8);
    }
    
    //fclose(rd);
    //fclose(wr);
    return;
}
