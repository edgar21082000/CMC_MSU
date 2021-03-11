#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

void proccess(int **fd_cmd,  int **fd, int proc_num, int N,  int val);

enum{
    P_NW = 0, P_N = 1, P_NE = 2,
    P_W = 3,         P_E = 4,
    P_SW = 5, P_S = 6, P_SE = 7,    
};

int main(int argc, char **argv){
    int i, j, status = 0;
    int N, seed = time(0);

    sscanf(argv[1], "%d", &N);
    if(argc == 3)
        sscanf(argv[2], "%d", &seed);
        
    srand(seed);
    setbuf(stdout, NULL);
    
    // fd[proc_num][direction][read/write]
    int **fd = (int **)malloc(N*N*sizeof(int *));
    for(i = 0; i < N*N; i++){
        fd[i] = (int *)malloc(2*sizeof(int));
        pipe(fd[i]);
    }
    
    printf(">>> >>>ENTER or 'q' for quit: ");
    
    int cmd[2];
    cmd[0] = getchar();
    cmd[1] = 0;
    
    int **fd_cmd = (int **)malloc(N*N*sizeof(int *));
    for(i = 0; i < N*N; i++){
        fd_cmd[i] = (int *)malloc(2*sizeof(int));
        pipe(fd_cmd[i]);
    }
    
    write(fd_cmd[0][1], cmd, 2*sizeof(int));

 
    
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
//printf("------\n%2d %2d %2d\n%2d %2d %2d\n%2d %2d %2d\n------\n", NW, Nr, NE, W, proc_num, E, SW, S, SE);    

    
    
    int tmp_read[8];
    int cnt_active, cur_prn_num;
    
    int c;
    int cmd[2];
    int r_byte, r_proc_num, proccess_this;

    while(1){
//printf(">>>[%d]: enter to whihe\n", proc_num);
        r_byte = read(fd_cmd[proc_num][0], cmd, 2*sizeof(int));
        // check proccess already done
        //proccess_this = 0;
        
//printf(">>>[%d]: I'M READ %d byte: {%d, %d}\n", proc_num, r_byte, cmd[0], cmd[1]);
        c = cmd[0];
        //r_proc_num = cmd[1];

        //if(r_proc_num == proc_num)
        //    proccess_this = 1;
//printf("\n>>>[%d]: check proccess: <%d>| pid_cnt = %d | flag = %d\n",proc_num, c, r_proc_num, proccess_this);
        //if(!proccess_this){
        //    if(r_proc_num <= N*N-1)
        //        write(fd_cmd[1], cmd, 2*sizeof(int));
        //    continue;    
        //}

        //-----------------------------
        
        if(c != 'q'){
            /*
            //print current val
            while(1){
                read(fd_print[0], &cur_prn_num, sizeof(int));

                if(cur_prn_num == proc_num){
                    printf("%d", *val); fflush(stdout);
                    if(proc_num % N == N-1){printf("\n"); fflush(stdout);}
                        
                    cur_prn_num++;
                    write(fd_print[1], &cur_prn_num, sizeof(int));
                    break;
                } else {
                    write(fd_print[1], &cur_prn_num, sizeof(int));
                }     
            }    
            //-----------------
            */
            printf("%d", state); fflush(stdout);
            if(proc_num % N == N-1){printf("\n"); fflush(stdout);}
                    
            
//printf("\n>>>[%d]: print_val\n", proc_num);        
            //send val to neighbours
            write( fd[NW][1], &state, sizeof(int));
            write( fd[Nr][1],  &state, sizeof(int));
            write( fd[NE][1], &state, sizeof(int));
            write( fd[W][1],   &state, sizeof(int));
            write( fd[E][1],   &state, sizeof(int));
            write( fd[SW][1], &state, sizeof(int));
            write( fd[S][1],   &state, sizeof(int));
            write( fd[SE][1], &state, sizeof(int));
            //----------------------
//printf("\n>>>[%d]: send val to neighbours\n", proc_num);
            //make mark process done
            if(proc_num < N*N-1)
                write(fd_cmd[proc_num+1][1], cmd, 8);

            //---------------------
//printf("\n>>>[%d]: make mark process done\n", proc_num);                             
            //get neighbours val
            cnt_active = 0;
            for(j = 0; j < 8; j++){
                read( fd[proc_num][0], &tmp_read[j], sizeof(*tmp_read));
                if(tmp_read[j] == 1) 
                    cnt_active++;
            }
            //---------------------
//printf("\n>>>[%d]: get neighbours val: %d\n", proc_num, cnt_active);           
            //change cells state
            prev_state = state;
            state = 0;
            switch(prev_state){
            case 0:
                if(cnt_active == 3){
                    state = 1; //printf(">>>[%d]: here1: cnt_active = %d\n", proc_num, cnt_active);
                }
                break;
            case 1:
                if(cnt_active == 2 || cnt_active == 3){
                    state = 1; //printf(">>>[%d]: here2: cnt_active = %d\n", proc_num, cnt_active);
                }
                break;
            default:
                break;
            }
            //---------------------
            if(proc_num == N*N - 1){
                printf(">>>ENTER or quit: ");
                cmd[0] = getchar();
                write(fd_cmd[0][1], cmd, 8);
            }
//printf("\n>>>[%d]: change cells state: %d -> %d \n", proc_num, prev, state);            

        } else {
            /*
            //print current val
            while(1){
                read(fd_print[0], &cur_prn_num, sizeof(int));
                if(cur_prn_num == proc_num){
                    printf("%d", *val);
                    if(proc_num % N == N-1)
                        printf("\n");
                    cur_prn_num++;
                    write(fd_print[1], &cur_prn_num, sizeof(int));
                } else {
                    write(fd_print[1], &cur_prn_num, sizeof(int));
                }     
            }
            //-----------------
            */
            
            /*
            printf("%d", state); fflush(stdout);
            if(proc_num % N == N-1){printf("\n"); fflush(stdout);}
            */
            cmd[0] = c;
            cmd[1] = proc_num;
            if(proc_num < N*N-1){
                cmd[0] = c;
                cmd[1] = proc_num;
                write(fd_cmd[proc_num+1][1], cmd, 2*sizeof(int));    
            } 
            
            
            break;  
        }
   }
   
   // disconnect_neighbours
    for(j = 0; j < N*N; j++){
        close(fd[j][0]);
        close(fd[j][1]);
        close(fd_cmd[j][0]);
        close(fd_cmd[j][1]);
    }
   //----------------------
//printf("\n>>>[%d]: disconnect_neighbours\n", proc_num);    
   
}
