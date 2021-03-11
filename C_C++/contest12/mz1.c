#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>



int main(int argc, char **argv)
{
    int n, key, maxval;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%d", &maxval);
         
    int sem_id = semget(key, n + 1, 0666 | IPC_CREAT | IPC_EXCL);
    semctl(sem_id, 1, SETVAL, 1);
    
    int shm_id = shmget(key, 2*sizeof(int), 0666 | IPC_CREAT);
    volatile int *p = shmat(shm_id, 0, 0);
    p[0] = 0;
    p[1] = 0;

    for (int i = 1; i <= n; i++) {
        if (!fork()) {
            struct sembuf down = { .sem_num = i, .sem_op = -1, .sem_flg = 0};
            
            while(1) {
                if (semop(sem_id, &down, 1) < 0) {
                    return 0;
                }
                
                printf("%d %d %d\n", i, p[0], p[1]);
                fflush(stdout);
                p[1] = i;                 
                
                p[0]++;
                if (*p > maxval) {
                    semctl(sem_id, 0, IPC_RMID);
                    shmctl(shm_id, IPC_RMID, 0);
                    return 0;
                }
                struct sembuf up =
                { .sem_num = (( (unsigned long long) (*p % n) * (*p % n) * (*p % n) * (*p % n)) % n + 1), 
                        .sem_op = 1, .sem_flg = 0 };  
    
                semop(sem_id, &up, 1);                    
            }
        }
    }
    wait(NULL);
    semctl(sem_id, 0, IPC_RMID);
    while(wait(NULL) != -1);
    
    shmctl(shm_id, IPC_RMID, 0);
    return 0;
}
