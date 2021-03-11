#include <stdio.h>

int main(void){
	unsigned int N;
	scanf("%u", &N);
	int kol = 0;
	while(N!=0){
		if(N%2==1) kol++;
		N>>=1;
	}
	printf("%d", kol);
	return 0;
}
