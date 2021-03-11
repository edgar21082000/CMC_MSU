#include <stdio.h>
#include <stdlib.h>

int main(void){
	int a[10000], N = 0, tmp;
	while(1){
		scanf("%d", &a[N]);
		if (a[N] == 0) break;
		N++;
	}
	
	for (int i = 0; i < N/2; i++){
		tmp = a[i];
		a[i] = a[N-1-i];
		a[N-1-i] = tmp;
	}
	
	for (int i = 0; i < N; i++) printf("%d ", a[i]);
	
	return 0;
}
