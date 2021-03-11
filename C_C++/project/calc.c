#include <stdio.h>
#include <stdlib.h>
#include "library.h"

//int iterations; //steps while find solution

double integral(double (*f)(double), double a, double b, double eps)
{
	int n = 1, i;
	double sum = 0., integral = 0., integral_cur = 0., plus, x, S0;
	
	plus = (b - a) / n;
	S0 = f(a) + f(b);
	while(1)
	{
		x = a;
		for(i=1; i<=n; i++)
		{
			x += plus;
			if(i%2) sum += f(x);	
		}
		
		integral_cur = (S0 + 2*sum)*((b-a)/(2*n));
		if(fabs(integral_cur - integral) < eps) break;
		
		integral = integral_cur;
		n*=2;
		plus/=2;	
	}
	return integral_cur;	
}

#ifdef hord
double root_secant_method(double (*f)(double), double (*g)(double), double a, double b, double eps)
{
	double x = a, x_cur, h_1, h_2;
	iterations = 0;
	
	while(1)
	{
		iterations++;
		h_1 = f(a) - g(a);
		h_2 = f(b) - g(b);
		x_cur = a - h_1*(b - a)/(h_2 - h_1);
		if(fabs(f(x_cur) - g(x_cur)) < eps) break;
		if ((f(a) - g(a)) * (f(x_cur) - g(x_cur)) < 0) {
			b = x_cur;
		}
		else {
			a = x_cur;
		}
	}
	return x_cur;
}
#endif

#ifdef newton
double root_newton_method(double (*f)(double), double (*g)(double), double (*df)(double), double (*dg)(double), double a, double b, double eps)
{
	double x = a/2 , x_cur, h, dh;
	iterations = 0;
	
	while(1)
	{
		iterations++;
		h = f(x) - g(x);
		dh = df(x) - dg(x);
		x_cur = x - h/dh;
		if(fabs(x_cur - x) <= eps) break;
		x = x_cur;
	}
	
	return x_cur;
}
#endif
