#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int fd[2];
    int sd[2];
    pipe(fd);
    pipe(sd);
    
    if(!fork()) {
        FILE *fin = fopen(argv[1], "r");
        double num;
        while(fscanf(fin, "%lf", &num) > 0) {
            if (num >= 0) {
                write(fd[1], &num, sizeof(num));
            }
        }
        fclose(fin);

        close(fd[1]);
        if (!fork()) {
            double sum = 0, t;
            int cnt = 0;
            while(read(fd[0], &t, sizeof(t))) {
                sum += t;
                cnt++;             
            }
            if (cnt) {
                write(sd[1], &sum, sizeof(sum));
            }
            
            close(sd[0]);
            close(sd[1]);
            close(fd[0]);
            return 0;
        }        

        close(sd[0]);
        close(sd[1]);     
        close(fd[0]);        
        wait(NULL);          

        return 0;
    }
    close(sd[1]);
    close(fd[1]);     
    close(fd[0]);
    wait(NULL);
    double rsum;    
    if((read(sd[0], &rsum, sizeof(rsum))) != sizeof(rsum)) {
        return 0;
    }
    printf("%.10g\n", rsum);
    close(sd[0]);
    return 0;
}
