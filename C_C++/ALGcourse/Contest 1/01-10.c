#include <stdio.h>
#include <math.h>

int main(void){
	unsigned int a, b, c, d, ans;
	scanf("%u%u%u%u", &a, &b, &c, &d );
	d<<=24;
	c<<=16;
	b<<=8;
	ans = a|b|c|d;
	printf("%u", ans);

	return 0;
}


