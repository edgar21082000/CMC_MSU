#include <stdio.h>

int main(void){
	int N, i, a1, a2, len_t, len_max;
	scanf("%d", &N);
	
	scanf("%d", &a1);
	len_t = 1;
	len_max = 1;
	
	for(i=1;i<N;i++){
		scanf("%d", &a2);
		
		if(a2>a1){
			len_t++;
			a1=a2;
		}
		else{
			if(len_t>len_max) len_max = len_t;
			a1 = a2;
			len_t = 1;
		}
	}
	if(len_t>len_max) len_max = len_t;
	printf("%d", len_max);
	return 0;
}
