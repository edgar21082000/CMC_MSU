#include <stdio.h>

void isosceles(double, double, double, double, double);

int main(void){
	double a1, a2, b1, b2, c1, c2;
	scanf("%lf %lf", &a1, &a2);
	scanf("%lf %lf", &b1, &b2);
	scanf("%lf %lf", &c1, &c2);
	
	double Cm1 = (a1+b1)/2; double Cm2 = (a2+b2)/2;
	double Bm1 = (a1+c1)/2; double Bm2 = (a2+c2)/2;
	
	//printf("C - %lf %lf\n", Cm1, Cm2 );
	//printf("B - %lf %lf\n", Bm1, Bm2 );
	
	//случай для равнобедренного треугольника нужно описать отдельно ибо происходит деление на 0
	
	/*if(c1-Cm1==0){
		isosceles(c1, b1, b2, Bm1, Bm2);
		return 0;
	}
	if(b1-Bm1==0){
		isosceles(b1, c1, c2, Cm1, Cm2);
		return 0;
	}*/
	
	// запишем уравнеия прямой для медиан С и В; найдем их коэффиценты и прировняем
	double k1, l;
	if(c1-Cm1>0 || c1-Cm1<0){
		k1 = (c2-Cm2)/(c1-Cm1);
		l = c2 - k1*c1;
		//printf("Cm: y=%lfx + %lf\n", k1, l);
	}
	else{
		isosceles(c1, b1, b2, Bm1, Bm2);
		return 0;	
	}
	
	double k2, n;
	if(b1-Bm1>0 || b1-Bm1<0){
		k2 = (b2-Bm2)/(b1-Bm1);
		n = b2 - k2*b1;
		//printf("Bm: y=%lfx + %lf\n", k2, n);
	}
	else{
		isosceles(b1, c1, c2, Cm1, Cm2);
		return 0;	
	}
	
	// Приравняем два уравнения прямы и найдем координаты точки переечения медиан
	
	double x = (n-l)/(k1-k2);
	double y = k1*x + l;
	
	printf("%.4lf %.4lf", x, y);
	return 0;
}

void isosceles(double x, double a1, double a2, double Am1, double Am2){
	double k, l;
	k = (a2-Am2)/(a1-Am1);
	l = a2 - k*a1;
	
	double y = k*x + l;
	printf("%.4lf %.4lf", x, y);
	return;
}
