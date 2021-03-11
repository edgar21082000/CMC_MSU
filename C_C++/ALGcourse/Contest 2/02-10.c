#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
	int N; scanf("%d", &N);
	double *s, *a, t = 0. , v0 = 0. , vk = 0. ;
	
	s = (double *)malloc(N*sizeof(double));
	a = (double *)malloc(N*sizeof(double));
	
	int i;
	
	for(i=0; i<N; i++) scanf("%lf", &s[i]);
	for(i=0; i<N; i++) scanf("%lf", &a[i]);
	
	for(i=0; i<N; i++){
		if ( (a[i] > 0) || (a[i] < 0) ){
			vk = sqrt(2*a[i]*s[i] + v0*v0);
			t += (vk - v0)/a[i];
			v0 = vk;
		}
		else t += s[i]/vk;
	}
	
	printf("%.4lf", t);
	free(s);
	free(a);
	
	return 0;
}
