#include <stdio.h>

int main(void){
	int a, b, sum = 0;
	unsigned int c;
	
	scanf("%u", &c);
	if(c%2 == 1){
		printf("%d\n", sum);
		return 0;
	}
	else{
		c>>=1;
		for(int i=0; i<c; i++)
		{
			scanf("%d", &a);
			scanf("%d", &b);
			
			sum = (a*b);
		}
	}
	
	printf("%d\n", sum);
	return 0;
}
