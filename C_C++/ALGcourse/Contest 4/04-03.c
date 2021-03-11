#include <stdio.h>
#include <string.h>

int main(void){
	char s[10001];
	scanf("%10000s", s);
	
	int n = strlen(s);
	
	for(int t=1; t<n; t++){
		int flag = 1;
		for(int i=t; (flag == 1) && (s[i] != '\0'); i++){
			if (s[i] == s[i-t]) flag = 1;
			else flag = 0;
		}
		if (flag==1) printf("%d ", t);
	}
	printf("%d", n); 
	
	return 0;
}
