#include <stdio.h>
#include <math.h>
// there are test functions with same name as in a main program
// so don't compile test.c and function.c together!!!  

double f1(double);
double f2(double);
double f3(double);

double f1(double x)
{
	return x*x;
}

double f2(double x)
{
	return cos(x);
}

double f3(double x)
{
	return exp(x);
}