#include <stdio.h>

int main(void){
	unsigned int a, b;
	scanf("%u", &a);
	b = a;
	b--;
	a = a^b;
	a += 1;
	a >>= 1;
	if(a == 0) a = 2147483648; // 2^31
	printf("%u\n", a);
	return 0; 
}
