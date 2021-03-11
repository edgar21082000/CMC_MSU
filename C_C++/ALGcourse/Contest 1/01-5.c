#include <stdio.h>

int main(void){
	int sum, a1, a2;
	scanf("%d", &sum);
	while(1){
		scanf("%d", &a1);
		if(a1 == 0) break;
		
		scanf("%d", &a2);
		if(a2 == 0){
			sum+=a1;
			break;
		}
		
		sum+=a1*a2;
	}
	printf("%d", sum);
	return 0;
}
