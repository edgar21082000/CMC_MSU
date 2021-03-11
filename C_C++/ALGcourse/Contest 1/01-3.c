#include <stdio.h>

int main(void){
	int N; 
	scanf("%d", &N);
	int k = 'z' - 'a' + 1;
	
	char let;
	while(1){
		scanf("%c", &let);
		if(let=='.') break;
		if(let==' ') {
			printf(" "); 
			continue;
		}
		
		if('a'<=let && let<='z') printf("%c", 'a' + (let - 'a' + N)%k);
		else printf("%c", 'A' + (let - 'A' +N)%k);
	}
	printf(".");
	return 0;	
}
