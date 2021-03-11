#include <stdio.h>
#include <stdlib.h>

int max(int, int, int);
void clear(int **, int);
void ans_print(int **, int, int);

int main(void){
	int n, m;
	scanf("%d%d", &n, &m);
	
	int **input;
	
	input = (int **)malloc(n*sizeof(int *));
	for(int i=0; i<n; i++)
		input[i] = (int *)calloc(m, sizeof(int));
	
	
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			scanf("%d", &input[i][j]);
	
		
	for(int j=1; j<m; j++){
		input[0][j] += max(0, input[0][j-1], input[1][j-1]);
		input[n-1][j] += max(input[n-2][j-1], input[n-1][j-1], 0);
		
		for(int i=1; i<n-1; i++)
			input[i][j] += max(input[i-1][j-1], input[i][j-1], input[i+1][j-1]);		 
	}	
	
	ans_print(input, n, m);
	clear(input, n);
	return 0;
}

int max(int a, int b, int c){
	int tmp = (a >= b ? a : b);
	return tmp >= c ? tmp : c; 
}

void ans_print(int **a, int n, int m){
	int ans = a[0][m-1];
	for(int i=1; i<n; i++)
		if(a[i][m-1] > ans)
			ans = a[i][m-1];
	
	printf("%d", ans); 
}

void clear(int **a, int N){
	for(int i=0; i<N; i++)
		free(a[i]);
	free(a);
	return ;
}


