#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

enum
{
    MAX = 10,
};

int main(int argc, char **argv)
{
    int count, key, n, iter;
    sscanf(argv[1], "%d", &count);
    sscanf(argv[2], "%d", &key);
    sscanf(argv[3], "%d", &n);
    sscanf(argv[4], "%d", &iter);
    
    int sem_id = semget(key, count, 0666 | IPC_CREAT | IPC_EXCL);
    for (int i = 0; i < n; i++) {
        semctl(sem_id, 0, SETVAL, 1);
    }
        
    int shm_id = shmget(key, count * sizeof(int), 0666 | IPC_CREAT);
    int *p = shmat(shm_id, 0, 0);
    for (int i = 0; i < count; i++) {
        scanf("%d", &p[i]);
    }
    
    for (int i = 0; i < n; i ++) {
        if (!fork()) {
            int seed;
            sscanf(argv[i + 5], "%d", &seed);
            srand(seed);
            
            for (int j = 0; j < iter; j++) {
                int i1 = (int)(count * rand() / (1. + RAND_MAX));
                int i2 = (int)(count * rand() / (1. + RAND_MAX));
                int val = (int)(MAX * rand() / (1. + RAND_MAX));
                
                if (i1 != i2) {
                    struct sembuf down[2] = { 
                        { .sem_num = i1, .sem_op = -1, .sem_flg = 0},
                        { .sem_num = i2, .sem_op = -1, .sem_flg = 0}
                    };  
                    semop(sem_id, down, 2);
                } else {
                    struct sembuf down = { .sem_num = i1, .sem_op = -1, .sem_flg = 0};
                    semop(sem_id, &down, 1);
                }
                
                operation(p, i1, i2, val);

                if (i1 != i2) {
                    struct sembuf up[2] = { 
                        { .sem_num = i1, .sem_op = 1, .sem_flg = 0},
                        { .sem_num = i2, .sem_op = 1, .sem_flg = 0}
                    };  
                    semop(sem_id, up, 2);
                } else {
                    struct sembuf up = { .sem_num = i1, .sem_op = 1, .sem_flg = 0};
                    semop(sem_id, &up, 1);
                }            
            }
            return 0;
        }
    }

    while(wait(NULL) != -1);
    semctl(sem_id, 0, IPC_RMID);
    for (int i = 0; i < count; i++) {
        printf("%d\n", p[i]);
    }
    shmctl(shm_id, IPC_RMID, 0);
    return 0;
}
