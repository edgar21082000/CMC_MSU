#include <stdio.h>
#include <math.h>


int int_cat(int m);

int main(void){
	int n, A;
	scanf("%d%d", &n, &A);
	
	if (A>=2010){
		printf("NO");
		return 0;
	}
	
	n%=2010;
	if (n == A){
		printf("YES");
		return 0;
	}
	
	for(int i=0; i<2010; i++){
		n = int_cat(n)%2010;
		if (n == A){
			printf("YES");
			return 0;
		}
	}
	
	printf("NO");
	return 0;
}

int int_cat(int n){
	int a = 0, n_tmp = n;
	while (n_tmp!=0){
		n_tmp/=10;
		a++;
	} 
	return n + n*(int)pow(10, a);
}
