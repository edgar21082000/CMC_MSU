#include <stdio.h>

int main(void){
	int N, i, max, tmp, kol;
	scanf("%d", &N);
	scanf("%d", &max);
	kol = 1;
	
	
	for(i=1;i<N;i++){
		scanf("%d", &tmp);
		
		if(tmp == max) {
			kol++;
			continue;
		}
		if(tmp>max){
			max = tmp;
			kol = 1;
		}
	}
	printf("%d", kol);
	return 0;
}
