#include <stdio.h>
#include <string.h>

enum {ml = 1000000};

int main(void){
	int n, i = 0, j = 0;
	scanf("%d\n	", &n);
	
	char s[ml+1];
	fgets(s, ml, stdin);
	int len = strlen(s)-1; 
	s[len] = '\0';
	
	int sp = 0;
	while(s[i]!='\0') if(s[i++]==' ') sp++;
	int space = n - (len-sp);
	
	if(sp==0){//если одно слово
		printf("%s", s);
		for(int i=0; i<space; i++) printf(" ");
		return 0;
	}
	
	int p = space%sp;
	int q = space/sp;
	for(i=0; i<p; i++){	//первые "длинные" пробелы
		while(s[j]!=' ')putchar(s[j++]);
		
		for(int k=0; k<q+1; k++) printf(" ");
		j++;
	}
	
	for(i=p; i<sp; i++){ //"короткие" пробелы
		while(s[j]!=' ') putchar(s[j++]);
		
		for(int k=0; k<q; k++) printf(" ");
		j++;
	}
	
	while(s[j]!='\0') putchar(s[j++]);	
	return 0;
}
