#include <stdio.h>

int main(void){
	int N, min, max, tmp, i;
	scanf("%d", &N);
	min = 10000000;
	max= -10000000;
	

	
	for(i=0;i<N;i++){
		scanf("%d", &tmp);
		if(tmp<min) min = tmp;
		if(tmp>max) max = tmp;
		
	}
	
	printf("%d", max - min);
	return 0;
}
