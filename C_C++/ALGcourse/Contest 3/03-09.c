#include <stdio.h>
#include <math.h>

void b_coordinate(double a1, double a2, double b1, double b2, double c1, double c2);

int main(void){
	double a1, a2, b1, b2, c1, c2;
	scanf("%lf%lf%lf%lf%lf%lf", &a1, &a2, &b1, &b2, &c1, &c2);
	
	b_coordinate(b1, b2, c1, c2, a1, a2);
	b_coordinate(c1, c2, a1, a2, b1, b2);
	b_coordinate(a1, a2, b1, b2, c1, c2);
	
	return 0;
}

void b_coordinate(double a1, double a2, double b1, double b2, double c1, double c2){
	double a = sqrt( pow(c2-b2, 2) + pow(c1-b1, 2) );
	double b = sqrt( pow(a2-c2, 2) + pow(a1-c1, 2) );
	double c = sqrt( pow(b2-a2, 2) + pow(b1-a1, 2) );
	
	//printf("a = %lf, b = %lf, c = %lf\n", a, b, c);
	
	double x = c*b/(a+c); 
	//printf("x = %lf\n", x);
	
	
	
	double x1 = (x*(c1 - a1) + a1*b)/b; 
	double x2 = (x*(c2 - a2) + a2*b)/b;
		
	printf("%.5lf %.5lf\n", x1, x2);
	return ;		
}
