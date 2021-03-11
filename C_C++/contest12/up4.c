#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>


int main(int argc, char **argv)
{
    int count;
    sscanf(argv[1], "%d", &count);
    
    int sem_id = semget(IPC_PRIVATE, count, 0666 | IPC_CREAT | IPC_EXCL);
    semctl(sem_id, 0, SETVAL, 1);
    
    for (int i = 0; i < count; i++) {
        if (!fork()) {
            setbuf(stdin, NULL);            
            while(1) {
                struct sembuf down = { .sem_num = i, .sem_op = -1, .sem_flg = 0};
                if (semop(sem_id, &down, 1) < 0)
                    return 0;
                int x;
                if (scanf("%d", &x) != 1) {
                    semctl(sem_id, 0, IPC_RMID);
                    return 0;
                }
                
                printf("%d %d\n", i, x);
                fflush(stdout);
                
                struct sembuf up = { .sem_num = (x % count + count) % count, .sem_op = 1, .sem_flg = 0};
                semop(sem_id, &up, 1);
            }        
        }
    }
    while(wait(NULL) != -1);
    semctl(sem_id, 0, IPC_RMID);
    return 0;
}
