#include <stdio.h>
#include <math.h>

int main(void){
	unsigned int N, mask;
	int K, i, tmp, max;
	scanf("%u%d", &N, &K);
	
	max = 0;
	mask = 0;
	for(i=0;i<K;i++) mask+=pow(2, i);
	
	for(i=0;i<=32-K;i++){
		tmp = N&mask;
		if(tmp>max) max = tmp;
		N>>=1;
	}
	printf("%d", max);
	return 0;
	
}
