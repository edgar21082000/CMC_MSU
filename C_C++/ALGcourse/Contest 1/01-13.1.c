#include <stdio.h>

int main(void){
	int N, i;
	double x, plus = 0, ans = 0;
	
	scanf("%lf%d", &x, &N);
	
	plus = x;
	for(i=1;i<=N;i++){
		ans+=plus;
		plus = (-1)*(plus*x*x)/((2*i)*(2*i+1));
	}
	printf("%6lf", ans);
	return 0;
}
