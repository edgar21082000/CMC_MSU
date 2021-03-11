#include <stdio.h>

int DPN(void);

int main(void){
	printf("%d", DPN());
	return 0;
}

int DPN(void){
	int a; char c;
	if (scanf("%d", &a) == 1) return a;
	else{
		scanf("%c", &c);
		if (c == '*') return DPN()*DPN();
		else return DPN()/DPN();
	}
}



