#include <stdio.h>
#include <stdlib.h>

int main(void){
	int N; scanf("%d", &N);
	int *a; a = (int *)malloc((N+1)*sizeof(int));
	
	int i, j, ans = 0;
	for(i=1; i<=N; i++) scanf("%d", &a[i]);
	
	for(i=1; i<=N-1; i++){
		for(j = i+1; j <= N; j++){
			if( (i+j)%2 == 1 ) continue;
			if( (a[i] + a[j])%2 == 0  &&  a[(i+j)/2] == (a[i] + a[j])/2 ) ans++;
		}
	}
	
	printf("%d", ans);
	free(a);
	
	return 0;
}
