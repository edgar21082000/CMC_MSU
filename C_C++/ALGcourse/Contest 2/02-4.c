#include <stdio.h>
#include <stdlib.h>

int max(int a, int b);

int main(void){
	int N, ans = 0, *a;
	scanf("%d", &N);
	a = (int *)malloc(2*N*sizeof(int));
	for(int i=0; i<2*N; i++) scanf("%d", &a[i]);
	for(int i=0; i<N; i++) ans += max(a[i], a[i+N]);
	printf("%d", ans);
	free(a);
	return 0;
}

int max(int a, int b){
	if (a >= b) return a;
	else return b;
}
