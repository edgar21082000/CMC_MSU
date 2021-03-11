#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b);
int prefix_function(char *, char *);

int main(void){
	char *s1, *s2;
	s1=(char *)malloc(10001*sizeof(char));
	s2=(char *)malloc(10001*sizeof(char));
	
	scanf("%10000s", s1);
	scanf("%10000s", s2);
	
	printf("%d %d", prefix_function(s1, s2), prefix_function(s2, s1));
	//printf("%d", prefix_function(s2, s1));
	
	free(s1);
	free(s2);
	
	return 0;
}

int prefix_function(char *s1, char *s2){
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	
	int max = 0, flag;
	for (int n=1; n<=min(l1 ,l2); n++){
		flag = 0;
		for (int i=0; i<n; i++){
			if (s1[i]==s2[l2-n+i]) flag = 1;
			else{
				flag = 0;
				break;
			}
		}
		if (flag == 1) max = n;
	} 
	return max;
}

int min(int a, int b) {return (a>=b) ? b : a;}
