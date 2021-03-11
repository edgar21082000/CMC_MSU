#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <limits.h>


typedef struct Val
{
    pid_t pid;
    long long num;
} Val;

int main(int argc, char **argv)
{
    int status;
    long long num;
    Val *arr = calloc(argc, sizeof(Val));
        
    for (int i = 1; i < argc; i++) {
        sscanf(argv[i], "%lld", &num);
        if (!(arr[i-1].pid = fork())) {
            free(arr);
            //unsigned long long num_t;
            if (num == LLONG_MIN) 
                return 2;
            

            long long sum = 0;
            if (num < 0) num *= -1;
            while (num) {
                sum += num % 4;
                num /= 4;
            }
            return sum;
        }   
    }
    
    
    pid_t pid1;
    while((pid1 = wait(&status)) != -1) {
        int i = 0;
        while (arr[i].pid != pid1) {
            i++;
        }
        arr[i].num = WEXITSTATUS(status);
    }
    
    for (int i = 0; i < argc - 1; i++) {
        printf("%lld\n", arr[i].num);
        fflush(stdout);
    }
    free(arr);
    return 0;
}


