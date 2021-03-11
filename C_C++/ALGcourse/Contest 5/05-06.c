#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	int L;
	char *s;
	scanf("%d", &L);
	s = (char *)malloc((L+1)*sizeof(char));
	scanf("%s", s);
	
	for(int i=0; i<strlen(s)/2; i++){
		if(s[i]!=s[strlen(s)-1-i]){
			printf("NO");
			free(s);
			return 0;
		}
	}
	
	free(s);
	printf("YES");
	return 0;
}
