#include <stdio.h>
#include <stdlib.h>

int N, max_sum = 0;

int solve(int *arr, int sum1, int sum2, int i);

int main(void){
	scanf("%d", &N);
	int *arr; arr=(int *)malloc(N*sizeof(int));
	for(int i=0; i<N; i++) scanf("%d", &arr[i]);
	
	int sum1 = 0, sum2 = 0;
	printf("%d", solve(arr, sum1, sum2, 0));
	free(arr); 
	return 0;
}

int solve(int *arr, int sum1, int sum2, int i){
	
	
	if (sum1 == sum2 && sum1 > max_sum) max_sum = sum1;
	if (i==N) return max_sum;
	
	//printf("%d %d %d\n", sum1, sum2, max_sum);
	//system("pause");
	
	solve(arr, sum1 + arr[i], sum2, i+1);
	solve(arr, sum1, sum2 + arr[i], i+1);
	solve(arr, sum1, sum2, i+1);
	return max_sum;
}
