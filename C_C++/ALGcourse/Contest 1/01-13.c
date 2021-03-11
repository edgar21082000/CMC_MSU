#include <stdio.h>

double power(double, int);
int fact(int);

int main(void){
	double X= 0.; 
	int N = 0, i;
	scanf("%lf", &X);
	scanf("%d", &N);
	
	double sin = 0. ;
	for(i=0;i<N;i++){
		sin+= power(-1., i+2)*power(X, 2*i+1)/fact(2*i+1);
	}
	printf("%6lf", sin);
	
	return 0;
	
}

double power(double x, int a){
	int i = 0;
	double res = 1.;
	for(i=0;i<a;i++) res*=x;
	return res;
}

int fact(int x){
	if(x==1) return 1;
	else return x*fact(x-1);
}
