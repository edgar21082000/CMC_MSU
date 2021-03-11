#include <stdio.h>
#include <stdlib.h>

int main(void){
	int a[10][10];
	int i, j, num, sum = 0;
	char let;
	
	for(i=1; i<=8; i++) for(j=1; j<=8; j++) a[i][j] = 1;
	
	while(scanf("%c%d", &let, &num)==2) for(i=-1; i<=1; i++) for(j=-1; j<=1; j++) a[let - 'a' + 1 + i][num + j] = 0;
	
	for(i=1; i<=8; i++) for(j=1; j<=8; j++) sum += a[i][j];
	printf("%d", sum);
	
	return 0;
}
