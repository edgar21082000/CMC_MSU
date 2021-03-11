#include <stdio.h>
#include <stdlib.h>

int main(void){
	int N; scanf("%d", &N);
	int *p, *ans, *dublicate;
	
	p = (int *)malloc((N+1)*sizeof(int));
	ans = (int *)malloc((N+1)*sizeof(int));
	dublicate = (int *)malloc((N+1)*sizeof(int));
	
	int i, j;
	
	for(i=1; i<=N; i++){
		scanf("%d", &p[i]);
		ans[i] = p[i];
		dublicate[i] = ans[i];
	}
	
	for(j=1; j<3; j++){
		for(i=1; i<=N; i++) ans[i] = dublicate[p[i]];
		for(i=1; i<=N; i++) dublicate[i] = ans[i];
	}
	
	for (i=1; i<=N; i++) printf("%d ", ans[i]);
	
	free(p);
	free(ans);
	free(dublicate);
	
	return 0;
}


