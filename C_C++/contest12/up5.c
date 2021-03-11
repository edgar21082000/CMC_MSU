#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void merge(FILE *in1, FILE *in2, FILE *res)
{
    int v1, v2, empty = 0;
    if (fscanf(in1, "%d", &v1) != 1) empty = 1;
    if (fscanf(in2, "%d", &v2) != 1) empty = 1;
    
    while (!empty) {
        if (v1 == v2) {
            fprintf(res, "%d ", v1);
            if (fscanf(in1, "%d ", &v1) != 1) empty = 1;
            if (fscanf(in2, "%d ", &v2) != 1) empty = 1;
        } else if (v1 > v2) {
            if (fscanf(in2, "%d ", &v2) != 1) empty = 1;
        } else {
            if (fscanf(in1, "%d ", &v1) != 1) empty = 1;
        }
    }
    fclose(in1);
    fclose(in2);
    fclose(res);
}

int main(int argc, char **argv)
{
    int n = argc - 1;
    if (n == 0) {
        printf("\n");
        return 0;
    }
    
    int *f = calloc(2*n-1, sizeof(int));
    int pos = 0;
    for (int i = 1; i <= n; i++) {
        f[pos++] = open(argv[i], O_RDONLY);
    }

    for (int i = 0; i < n - 1; i++) {
        int fd[2];
        pipe(fd);
        f[pos++] = fd[0];
        
        if (!fork()) {
            FILE *in1 = fdopen(f[2*i], "r");
            FILE *in2 = fdopen(f[2*i+1], "r");
            FILE *res = fdopen(fd[1], "w");
            
            merge(in1, in2, res);
            
            close(f[2*i]);
            close(f[2*i+1]);
            close(fd[0]);
            close(fd[1]);
            return 0;
        }
        close(f[2*i]);
        close(f[2*i+1]);
        close(fd[1]);
    }
    
    FILE *res = fdopen(f[pos-1], "r");
    int x;
    while(fscanf(res, "%d", &x) == 1) {
        printf("%d ", x);
    }
    printf("\n");
    fclose(res);
    while(wait(NULL) != -1);
    free(f);
    return 0;
}
