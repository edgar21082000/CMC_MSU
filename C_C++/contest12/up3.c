#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>  

struct Msgbuf
{
    long mtype;
    long long val[2];
};  

void killall(pid_t *arr, int ind)
{
    for (int i = 0; i < ind; i++)
        kill(arr[i], SIGKILL);

    while(wait(NULL) != -1);
    free(arr);
}

int main(int argc, char **argv)
{
    int n, key;
    long long val[2], maxval;
    sscanf(argv[1], "%d", &key); 
    sscanf(argv[2], "%d", &n);
    sscanf(argv[3], "%lld", &val[0]);
    sscanf(argv[4], "%lld", &val[1]);
    sscanf(argv[5], "%lld", &maxval);

    pid_t *pid_arr = calloc(n, sizeof(pid_t));
    int msg_id = msgget(key, IPC_CREAT | 0666);
    
    int ind = 0;
    for (int i = 0; i < n; i++) {
        if (!(pid_arr[ind++] = fork())) {
            while(1) {
                struct Msgbuf data;
                if((msgrcv(msg_id, &data, sizeof(data) - sizeof(long), i+1, 0)) < 0) return 0;
                long long sum = data.val[0] + data.val[1];
                printf("%d %lld\n", i, sum);
                fflush(stdout);
                
                if (sum > maxval) {
                    msgctl(msg_id, IPC_RMID, 0);
                    return 0;
                }
                
                data.val[0] = data.val[1];
                data.val[1] = sum;
                data.mtype = sum % n + 1;
                msgsnd(msg_id, &data, sizeof(data) - sizeof(long), 0);
            }
        } else if (pid_arr[ind-1] == -1) {
            killall(pid_arr, ind);
            msgctl(msg_id, IPC_RMID, 0);
            exit(1);
        }
    }
    struct Msgbuf begin;
    begin.mtype = 1;
    begin.val[0] = val[0];
    begin.val[1] = val[1];
    msgsnd(msg_id, &begin, sizeof(begin) - sizeof(long), 0);
    
    while(wait(NULL) != -1);
    free(pid_arr);    
    msgctl(msg_id, IPC_RMID, 0);
    return 0;
}


