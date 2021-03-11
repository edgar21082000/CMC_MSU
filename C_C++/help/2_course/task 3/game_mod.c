#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

void proccess(int **fd_cmd, int **fd, int proc_num, int N,  int val);

int main(int argc, char **argv){
    int i, j;
    int N, seed = time(0);

    sscanf(argv[1], "%d", &N);
    if(argc == 3)
        sscanf(argv[2], "%d", &seed);
        
    srand(seed);
    setbuf(stdout, NULL);
    
    // fd[proc_num][direction][read/write]
    int **fd = (int **)malloc(N*N*sizeof(int *));
    int **fd_cmd = (int **)malloc(N*N*sizeof(int *));
    for(i = 0; i < N*N; i++){
        fd[i] = (int *)malloc(2*sizeof(int));
        pipe(fd[i]);
        fd_cmd[i] = (int *)malloc(2*sizeof(int));
        pipe(fd_cmd[i]);    
    }
    
    printf(">>>ENTER or 'q' for quit: ");
    int c = getchar();
    write(fd_cmd[0][1], &c, sizeof(int));  
    
    int val = rand()%2;     
    // create (N^2-1) child-proccess; proccess # N^2 is parent
    for(i = 0; i < N*N - 1; i++){
        if(!fork()){ // childs    
            for(j = 0; j <= i; j++)
                val = rand()%2;
            
            proccess(fd_cmd, fd, i, N, val);
            return 0;
        }
    }

    proccess(fd_cmd, fd, N*N-1, N, val);
    
    while(wait(NULL) != -1);
    
    return 0;
}

void proccess(int **fd_cmd, int **fd, int proc_num, int N,  int val){
    int i, j;
    int prev_state, state = val;
    
    int NW, Nr, NE;
    int  W,     E;
    int SW, S, SE;
    
    int col, row;
    col = proc_num % N;
    row = proc_num / N;
    
    // neighbours_connect
    NW = (row-1 < 0 ? N-1 : row-1)*N + (col-1 < 0 ? N-1 : col-1);
    Nr =  (row-1 < 0 ? N-1 : row-1)*N + col;
    NE = (row-1 < 0 ? N-1 : row-1)*N + (col+1)%N;
    W = row*N + (col-1 < 0 ? N-1 : col-1);
    E = row*N + (col+1)%N;
    SW = ((row+1)%N)*N + (col-1 < 0 ? N-1 : col-1);
    SE = ((row+1)%N)*N + (col+1)%N;
    S = ((row+1)%N)*N + col;
    //--------------------    
    int tmp_read[8];
    int cnt_active, cur_prn_num;
    int c;
    
    while(1){    
        read(fd_cmd[proc_num][0], &c, sizeof(int));
       
        if(c != 'q'){
            printf("%d", state); fflush(stdout);
            if(proc_num % N == N-1){printf("\n"); fflush(stdout);}
                            
            //send val to neighbours
            write( fd[NW][1], &state, sizeof(int));
            write( fd[Nr][1], &state, sizeof(int));
            write( fd[NE][1], &state, sizeof(int));
            write( fd[W][1],  &state, sizeof(int));
            write( fd[E][1],  &state, sizeof(int));
            write( fd[SW][1], &state, sizeof(int));
            write( fd[S][1],  &state, sizeof(int));
            write( fd[SE][1], &state, sizeof(int));
            //----------------------

            //make mark process done            
            if(proc_num < N*N-1)
                write(fd_cmd[proc_num+1][1], &c, sizeof(int));
            //---------------------
                             
            //get neighbours val
            cnt_active = 0;
            for(j = 0; j < 8; j++){
                read( fd[proc_num][0], &tmp_read[j], sizeof(*tmp_read));
                if(tmp_read[j] == 1) 
                    cnt_active++;
            }
            //---------------------

            //change cells state
            prev_state = state;
            state = 0;
            switch(prev_state){
            case 0:
                if(cnt_active == 3)
                    state = 1; 
                break;
            case 1:
                if(cnt_active == 2 || cnt_active == 3)
                    state = 1;
                break;
            default:
                break;
            }
            //---------------------
            if(proc_num == N*N - 1){
                printf(">>>ENTER or quit: ");
                c = getchar();
                write(fd_cmd[0][1], &c, sizeof(int));
            }
         

        } else {
            if(proc_num < N*N-1)
                write(fd_cmd[proc_num+1][1], &c, sizeof(int));    
            break;  
        }
   }
   
   // disconnect_neighbours
    for(j = 0; j < N*N; j++){
        close(fd[j][0]);
        close(fd[j][1]);
        close(fd_cmd[j][0]);
        close(fd_cmd[j][1]);
        
        free(fd[j]);
        free(fd_cmd[j]);
    }
   //---------------------
    free(fd);
    free(fd_cmd);    
}
