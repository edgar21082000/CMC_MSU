#include <stdio.h>
#include <stdlib.h>

int N, **table;

void move(int x, int y, int k);
void next_step(int x, int y, int k);
int exit_status(int k);
void clear(int **a, int N);

int main(void){
	scanf("%d", &N);
	
	int i, j;
	
	table = (int **)malloc((N+1)*sizeof(int *));
	for(i=0; i<=N; i++) table[i] = (int *)malloc((N+1)*sizeof(int));
	
	for(i=0; i<=N; i++){
		for(j=0; j<=N; j++){
			table[i][j] = -1;
		}
	}
	
	int x, y, x_end, y_end;
	scanf("%d%d%d%d", &x, &y, &x_end, &y_end);
	
	if( (N==3) && ((x==2 && y==2) || (x_end==2 && y_end==2)) ){
		printf("-1");
		return 0;
	}
	move(x, y, 0);	

	printf("%d", table[x_end][y_end]);
	clear(table, N+1);
	
	return 0;
}

void move(int x, int y, int k){
	if(exit_status(k)) return;
	if(x<1 || x>N || y<1 || y>N) return;
	
	if(table[x][y] == -1 || table[x][y] > k){
		table[x][y] = k;
		next_step(x, y, k);
	}
	
	return;
}

int exit_status(int k){
	if(N>=6){
		 if(k==N-1) return 1;
	}
	else if(N==5){
		if(k==5) return 1;
	}
	else if(N==4){
		if(k==6) return 1;	
	} 
	else if(N==3){
		if(k==5) return 1;
	}
	
	return 0; 
}

void next_step(int x, int y, int k){
	move(x+1, y+2, k+1);
	move(x+2, y+1, k+1);
	move(x+2, y-1, k+1);
	move(x+1, y-2, k+1);
	move(x-1, y-2, k+1);
	move(x-2, y-1, k+1);
	move(x-2, y+1, k+1);
	move(x-1, y+2, k+1);
	return ;
}

void clear(int **a, int N){
	for(int i=0; i<N; i++)
		free(a[i]);
	free(a);
	return ;
}
