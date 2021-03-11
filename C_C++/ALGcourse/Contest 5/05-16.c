#include <stdio.h>
#include <stdlib.h>

/*
	10
	2000000000
	200000
	100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 
	100000 100000 100000 100000 100000 100000 100000 100000 100000 100000 
*/

void sdvig(int *, int, int);

int main(void){
	int k, N, p, *A, *F;
	scanf("%d%d%d", &k, &N, &p);
	
	F = (int *)malloc(k*sizeof(int));
	A = (int *)malloc(k*sizeof(int));
	
	for(int i=0; i<k; i++)
		scanf("%d", &F[i]);
		
	for(int i=0; i<k; i++)
		scanf("%d", &A[i]);
	
	int next = 0;	
	for(int i=k; i<N; i++){
		next = 0;
		for(int j=0; j<k; j++){
			next += A[j]*F[k-1-j];
			if(next >= p)
			next%=p;
		}
		
		sdvig(F, k, next);
		//printf("%d) %d\n", i+1, F[i]); 
	}
		
	
	printf("%d", F[k-1]);
	
	free(F);
	free(A);
	return 0;
}

void sdvig(int *F, int k, int next){
	for(int i=0; i<k; i++)
		F[i] = F[i+1];
	F[k-1] = next;
}
