#include <stdio.h>
#include <stdlib.h>

enum{
    LINK_CNT = 0, 
    TRUE = 1, FALSE = 0,
};

void start_trip(int **, int, int, int *, int *, int, int);
void print_way(int *, int);
void memory_clean(int **, int *, int,  int *);

int main(void){
    int N_points, S_point, F_point;
    int R_cnt = 0, link_cnt = 0;
    scanf("%d%d%d", &N_points, &S_point, &F_point);
    
    int **adj_matrix = NULL;
    
    for(int i = 1; i <= N_points; i++){ // построение таблицы смежности
        scanf("%d", &link_cnt);
        if(link_cnt){
            R_cnt += link_cnt;
        
            if(!adj_matrix)
                adj_matrix = calloc((N_points + 1), sizeof(int *)); // для удобства индексации
            
            adj_matrix[i] = (int *)malloc((link_cnt + 1) * sizeof(int));
            adj_matrix[i][LINK_CNT] = link_cnt;
            for(int j = 1; j < link_cnt + 1; j++)
                scanf("%d", &adj_matrix[i][j]);
        }
    }
    R_cnt /= 2; // кол-во ребер
        
    printf("\n");
    if(adj_matrix != NULL){
        int *blocked_points = calloc(N_points + 1, sizeof(int));
        int *way = (int *)malloc((R_cnt + 1) * sizeof(int));
        int cur_way_len = 0;
        start_trip(adj_matrix, S_point, F_point, blocked_points, way, cur_way_len, R_cnt);
        memory_clean(adj_matrix, blocked_points, N_points, way);
    }
        
    return 0;
}

void start_trip(int **adj_matrix, int cur_point, int F_point, 
        int *blocked_points, int *way, int cur_way_len, int R_cnt){
/*{
    printf("current - %d\n", cur_point);
    for(int i = 1; i <= 5; i++) printf("%d ", blocked_points[i]); printf("\n");
    for(int i = 0; i < cur_way_len; i++) printf("%d ", way[i]); printf("\n");
    int status; scanf("%d", &status);
}*/        
    if(cur_way_len > R_cnt) return;
    
    blocked_points[cur_point] = TRUE;
    way[cur_way_len++] = cur_point;
    if(cur_point == F_point){
        print_way(way, cur_way_len);
        blocked_points[cur_point] = FALSE;
        return;
    }
    if(adj_matrix[cur_point] != NULL){
        for(int i = 1; i <= adj_matrix[cur_point][LINK_CNT]; i++)
            if(!blocked_points[adj_matrix[cur_point][i]])
                start_trip(adj_matrix, adj_matrix[cur_point][i], F_point, blocked_points, way, cur_way_len, R_cnt);
        blocked_points[cur_point] = FALSE;    
    }
}

void print_way(int *way, int len){
    printf("%d ", len);
    for(int i = 0; i < len; i++)
        printf("%d ", way[i]);
    printf("\n");
}

void memory_clean(int **a, int *b, int N, int *c){
    free(b);
    free(c);
    
    for(int i=0; i <=N; i++)
        if(a[i] != NULL) 
            free(a[i]);
    free(a);   
}
