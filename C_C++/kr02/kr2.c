#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

typedef struct Bits
{
    pid_t pid;
    int value;
} Bt;

int main(int argc, char **argv)
{
    int status;
    long long num;
    Bt *arr = calloc(argc, sizeof(Bt));
        
    for (int i = 1; i < argc; i++) {
        sscanf(argv[i], "%lld", &num);
        if (!(arr[i-1].pid = fork())) {
            free(arr);
            unsigned long long mask = 1, cnt = 0;
            while (mask) {
                if (mask & num) {
                    cnt++;
                }
                mask <<= 1;
            }
            return cnt;
        }   
    }
    
    
    pid_t pid1;
    while((pid1 = wait(&status)) != -1) {
        int i = 0;
        while (arr[i].pid != pid1) {
            i++;
        }
        arr[i].value = WEXITSTATUS(status);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        printf("%d\n", arr[i].value);
    }
    free(arr);
    return 0;
}
    
