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

unsigned int p_adr_m[3] = { 0x00FFFFFF, 0x0000FFFF, 0x000000FF };

void work(unsigned int adr, int p_num)
{
    printf("%d %x\n", p_num + 1, adr & p_adr_m[p_num]);
    fflush(stdout);

}

int main(int argc, char **argv)
{
    setbuf(stdin, NULL);

    int sem_id = semget(IPC_PRIVATE, 4, 0666 | IPC_CREAT | IPC_EXCL);
    //for (int i = 0; i < 4; i++) {
    //    semctl(sem_id, 0, SETVAL, 1);
    //}
        
    int shm_id = shmget(IPC_PRIVATE, 1 * sizeof(int), 0666 | IPC_CREAT);
    unsigned int *p = shmat(shm_id, 0, 0);
    
    pid_t pid_arr[3];
    
    for(int i = 0; i < 3; i++) {
        if(!(pid_arr[i] = fork())) {
            while (1) {
                struct sembuf down = { .sem_num = i+1, .sem_op = -1, .sem_flg = 0};
                semop(sem_id, &down, 1);
                
                work(p[0], i);
                    
                struct sembuf up = { .sem_num = 0, .sem_op = 1, .sem_flg = 0};
                semop(sem_id, &up, 1);
            }
        }
    }
    while(scanf("%o", &p[0]) == 1) {
        if ((p[0] >> 31) == 0) {
                struct sembuf up = { .sem_num = 1, .sem_op = 1, .sem_flg = 0};
                semop(sem_id, &up, 1);

                struct sembuf down = { .sem_num = 0, .sem_op = -1, .sem_flg = 0};
                semop(sem_id, &down, 1);
            
        } else if ((p[0] >> 30) == 2u) {
                struct sembuf up = { .sem_num = 2, .sem_op = 1, .sem_flg = 0};
                semop(sem_id, &up, 1);

                struct sembuf down = { .sem_num = 0, .sem_op = -1, .sem_flg = 0};
                semop(sem_id, &down, 1);
        } else if ((p[0] >> 29) == 6u) {
                struct sembuf up = { .sem_num = 3, .sem_op = 1, .sem_flg = 0};
                semop(sem_id, &up, 1);

                struct sembuf down = { .sem_num = 0, .sem_op = -1, .sem_flg = 0};
                semop(sem_id, &down, 1);
        }
    }
        

    for(int i = 0; i < 3; i++) kill(pid_arr[i], SIGTERM);

    while(wait(NULL) != -1);
    semctl(sem_id, 0, IPC_RMID);
    shmctl(shm_id, IPC_RMID, 0);
    
    
    return 0;
}
