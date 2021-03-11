#include <stdio.h>

int main(void){
	int N, i, num, mask = 0;
	scanf("%d", &N);
	for(i=0;i<N;i++){
		scanf("%d", &num);
		mask^=num;
	}
	printf("%d", mask);
	return 0;
}
