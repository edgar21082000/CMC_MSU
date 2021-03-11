#include <stdio.h>

int seq(int i);

int main(void){
	int n; scanf("%d", &n);
	printf("%d", seq(n));
	return 0;
}

int seq(int i){
	if (i<=3) return i;
	if (i%2 == 0) return 3 + seq(i/2);
	else return 2*seq(i+3);
}


