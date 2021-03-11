#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int p[1000001];
int prefix_function(char *);

int main(void){
	char *s;
	s=(char *)malloc(1000001*sizeof(char));
	scanf("%1000000s", s);
	int n = strlen(s); 
	
	int t = n - prefix_function(s);
	int t_ = t; 
	
	while(t < n){
		printf("%d ", t);
		t += t_;
	}
	t-=t_;
	
	int j = 0;
	while(s[0] == s[strlen(s)-j-1]) j++;
	for(int i = strlen(s)-j; i <= n; i++) 
		if(i > t) 
			printf("%d ", i);
	 
	free(s); 
	return 0;
}

int prefix_function(char *s) {
	int len = strlen(s);
    p[0] = 0;
    
    int k = 0, i;
    for (i = 1; i<len; i++) {
        while (k > 0 && (s[i] != s[k]))
            k = p[k - 1];
        if (s[i] == s[k])
            k++;
        p[i] = k;
    }
    return p[len-1];
}
