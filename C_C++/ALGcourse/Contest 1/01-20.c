#include <stdio.h>
#include <math.h>

double maxi(double, double);
double mini(double, double);

int main(void){
	double a, b, c, d;
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	
	double L1, W1, L2, W2;
	
	L1 = maxi(a, b); W1 = mini(a, b);
	L2 = maxi(c, d); W2 = mini(c, d);
	
	
	double d1, d2; 
	
	d1 = a*a + b*b; 
	d2 = c*c + d*d;
	
	if (d2 > d1){
		printf("NO");
		return 0;
	}
	
	if (W2 > W1){
		printf("NO");
		return 0;
	}
	else if (W2 >= W1){ // == for double
		if (L1 >= L2){
			printf("YES");
			return 0;
		}
		else{
			printf("NO");
			return 0;
		}
	}
	else if (W2 < W1){
		if (L1 >= L2){
			printf("YES");
			return 0;
		}
	}
	
	if (L1 >= L2){
			printf("YES");
			return 0;
	}
	
    double q1, q2;
    q1 = L1/2 - sqrt(d2/4 - (W1*W1)/4);
    q2 = W1/2 - sqrt(d2/4 - (L1*L1)/4);
    
    if (q1*q1 + q2*q2 >= W2*W2){
    	printf("YES");
    	return 0;
	}
	else{
		printf("NO");
		return 0;
	}
	
	printf("YES");
	
	return 0;
}

double maxi(double a, double b){
	if (a>b) return a;
	else return b;
}

double mini(double a, double b){
	if (a<b) return a;
	else return b;
}
