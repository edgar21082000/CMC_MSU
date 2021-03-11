#include <stdio.h>
#include <math.h>

int main(void){
	unsigned int N, ans = 0;
	scanf("%u", &N);
	
	unsigned m24 = pow(2, 24) - 1;
	unsigned m8 = pow(2, 32) - 1 - m24;
	
	ans+=N&m24;
	
	unsigned N8 = N&m8;
	unsigned N8_new = ~N8;
	N8_new&=m8;
	
	ans+=N8_new;
	printf("%u", ans);
	
	return 0; 
}
