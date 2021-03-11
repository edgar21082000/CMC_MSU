#include <math.h>

int iterations;

double f1(double);
double f2(double);
double f3(double);

double df1(double);
double df2(double);
double df3(double);

double root_newton_method(double (*)(double), double (*)(double), double (*)(double), double (*)(double), double, double, double);
double root_secant_method(double (*)(double), double (*)(double), double, double, double);
double integral(double (*)(double), double, double, double);
