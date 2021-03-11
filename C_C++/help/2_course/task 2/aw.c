#include <stdio.h>
#include <stdlib.h>

struct Pair{
    int in;
    int out;
} typedef Pair;

struct L1{
    struct L1 *next;
    Pair p;
} typedef L1;

int way_cnt = 0;

void print_trip(L1 *, int, int, int *, int, int);
void count_trip(L1 *, int, int, int *, int, int);
int check_point(int, int *, int);
void print_way(int *, int);
L1 * init_L1(int);
L1 * add_L1(L1 *, int);

int main(void){
    int N_points, S_point, F_point;
    int R_cnt = 0, link_cnt = 0;
    int cur_way_len;
    int i, j;
    
    scanf("%d%d%d", &N_points, &S_point, &F_point);

    L1 *begin = NULL, *cur;
    
    
    for(i = 1; i <= N_points; i++){
        scanf("%d", &link_cnt);
        if(link_cnt){
            R_cnt += link_cnt;
            
            for(j = 0; j < link_cnt; j++){
                if(begin == NULL){
                    begin = init_L1(i);
                    cur = begin;
                }
                else
                    cur = add_L1(cur, i); 
            }
        }
    }
    
    R_cnt /= 2;
    if(begin != NULL){ // есть ребра   
        int *way = (int *)malloc((R_cnt + 1) * sizeof(int));
        cur_way_len = 0;
        count_trip(begin, S_point, F_point, way, cur_way_len, R_cnt);
        printf("%d\n", way_cnt);
        print_trip(begin, S_point, F_point, way, cur_way_len, R_cnt);
        free(way); 
    } else { // нет ребер
        if(S_point == F_point){
            printf("%d\n", way_cnt + 1);
            printf("1 %d\n", S_point);
        } else
            printf("%d\n", way_cnt);            
    }
        
    
    while(begin){
        cur = begin;
        begin  = cur->next;
        free(cur);
    }

    return 0;
}

void print_trip(L1 *begin, int cur_point, int F_point, 
        int *way, int cur_way_len, int R_cnt){

    if(cur_way_len > R_cnt)
        return; 
 
    L1 *cur = begin;
    while(cur && cur->p.in != cur_point)
        cur = cur->next;
        
    way[cur_way_len++] = cur_point;
    if(cur_point == F_point){
        print_way(way, cur_way_len);
        return;
    }
    
    while(cur && cur->p.in == cur_point){ // if cur->next
        if(!check_point(cur->p.out, way, cur_way_len))
            print_trip(begin, cur->p.out, F_point, way, cur_way_len, R_cnt);
            
        cur = cur->next;
    }
}

void count_trip(L1 *begin, int cur_point, int F_point, int *way, int cur_way_len, int R_cnt){
    
    if(cur_way_len > R_cnt)
        return;
    
    if(cur_point == F_point){
        way_cnt++; 
        return;
    }
        
    L1 *cur = begin;
    while(cur && cur->p.in != cur_point)
        cur = cur->next;
    
    way[cur_way_len++] = cur_point;
        
    while(cur && cur->p.in == cur_point){ // if cur->next
        if(!check_point(cur->p.out, way, cur_way_len))
            count_trip(begin, cur->p.out, F_point, way, cur_way_len, R_cnt);         

        cur = cur->next;
    }
}

int check_point(int new_p, int *way, int cur_way_len){
    int i;
    for(i = 0; i < cur_way_len; i++)
        if(new_p == way[i])
            return 1;
    return 0;
}

void print_way(int *way, int len){
    int i = 0;
    printf("%d ", len);
    for(i = 0; i < len; i++)
        printf("%d ", way[i]);
    printf("\n");
}

L1 * init_L1(int i){
    L1 *tmp = (L1 *)malloc(sizeof(L1));
    tmp->p.in = i;
    scanf("%d", &(tmp->p.out));
    tmp->next = NULL;
    return tmp;
}

L1 * add_L1(L1 *cur, int i){
    L1 *tmp = (L1 *)malloc(sizeof(L1));
    tmp->p.in = i;
    scanf("%d", &(tmp->p.out));
    tmp->next = NULL;
    
    cur->next = tmp;
    return cur->next;
}
