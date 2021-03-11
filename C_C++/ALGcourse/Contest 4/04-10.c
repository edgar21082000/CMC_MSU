#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*test
sadasdadasdsdf
sdfvsdvsdfvsdfsada

asddfgdsfadsdsdasd
sdsdassdasfdasd
*/

int p[2000001];
int prefix_function(char *);

int main(void){
	char *s1, *s2, *a, *b;
	a = (char *)malloc(1000001*sizeof(char));
	b = (char *)malloc(1000001*sizeof(char));
	s1 = (char *)malloc(2000001*sizeof(char));
	s2 = (char *)malloc(2000001*sizeof(char));
	
	scanf("%1000000s", a);
	scanf("%1000000s", b);
	
	strcpy(s1, a);
	s1[strlen(a)] = '@';
	strcat(s1, b);
	s1[strlen(a)+1+strlen(b)+1] = '\0';
	
	strcpy(s2, b);
	s2[strlen(b)] = '@';
	strcat(s2, a);
	s2[strlen(a)+1+strlen(b)+1] = '\0';
	
	printf("%d %d", prefix_function(s1), prefix_function(s2));
	
	free(a);
	free(b);
	free(s1);
	free(s2);
	
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

