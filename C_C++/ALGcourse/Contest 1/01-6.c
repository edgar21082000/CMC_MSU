#include <stdio.h>

int main(void){
	unsigned int N;
	int K, i;
	scanf("%u%d", &N, &K);
	for(i=0;i<K;i++){
		if(N%2 == 1){
			N>>=1;
			N+=2147483648;
			continue;
		}
		else N>>=1;
	}
	printf("%u", N);
	return 0;
}
