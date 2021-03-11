#include <stdio.h>
#include <math.h>

int main(void){
	unsigned int N;
	scanf("%u", &N);
	
	int K, res, i;
	scanf("%d", &K);
	res = 0;
	
	for(i=0;i<K;i++){
		if(N%2==1){
			N>>=1;
			res+=pow(2, i);
		}
		else N>>=1;
	}
	printf("%d", res);
	return 0;
	
}
