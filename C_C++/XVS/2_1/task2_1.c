#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum
{
	NOSYS = 0,
	SYS = 1,
};

// начальные аргументы
const double e = 2.7182818284;
double nosys_args[2] = {0., 3.};
double sys_args[3] = {0., 1., 0.25,};

double f1(double x, double y);
double f1_exac(double x, double y);
double test2(double x, double y);
double test2_exac(double x, double y);
double test3(double x, double y);
double test3_exac(double x, double y);

double f1_sys(double x, double y, double z);
double f2_sys(double x, double y, double z);
//double f1_sys_exac(double x, double y, double z);
//double f2_sys_exac(double x, double y, double z);

void runge_kutta_2(double (*f)(double, double), double *x, double *y, double h, int n, FILE *out);
void runge_kutta_4(double (*f)(double, double), double *x, double *y, double h, int n, FILE *out);
void runge_kutta_sys_2(double (*f)(double, double, double), double (*g)(double, double, double), double *x, double *y, double *z, double h, int n, FILE *out);
void runge_kutta_sys_4(double (*f)(double, double, double), double (*g)(double, double, double), double *x, double *y, double *z, double h, int n, FILE *out);

int main(int argc, char **argv)
{
	int mode, accur;
	sscanf(argv[1], "%d", &mode);
	sscanf(argv[2], "%d", &accur);
	
	printf("Enter [a, b] and n:\n");
	double a, b; int n;
	scanf("%lf%lf%d", &a, &b, &n);	
	double h = (b - a) / n;

	char name[128];
	sprintf(name, "table_%d_%d.txt", mode, accur);
	// файл для записи сетки и построения графика
	FILE *out = fopen(name, "w");

	// аргументы сетки сохраняются
	double *x = calloc(n + 1, sizeof(double));	
	double *y = calloc(n + 1, sizeof(double));
	double *z = calloc(n + 1, sizeof(double));

	if (mode == NOSYS) {
		x[0] = nosys_args[0];
		y[0] = nosys_args[1];	

		if (accur == 2) 
			runge_kutta_2(&f1, x, y, h, n, out);
		if (accur == 4)
			runge_kutta_4(&f1, x, y, h, n, out);
	}
	
	if (mode == SYS) {
		x[0] = sys_args[0];
		y[0] = sys_args[1];
		z[0] = sys_args[2];
	
		if (accur == 2)
			runge_kutta_sys_2(&f1_sys, &f2_sys, x, y, z, h, n, out);
		if (accur == 4)
			runge_kutta_sys_4(&f1_sys, &f2_sys, x, y, z, h, n, out);
	}	
	return 0;
}

void runge_kutta_2(double (*f)(double, double), double *x, double *y, double h, int n, FILE *out)
{
    for(int i = 0; i < n; i++) {
        fprintf(out, "%9.3lf %9.3lf ", x[i], y[i]);
		fprintf(out, "%9.3lf\n", f1_exac(x[i], y[i]));
        double k1 = (*f)(x[i], y[i]);
        double k2 = (*f)(x[i] + h, y[i] + h * k1); // пересчет tilda <y>
        y[i + 1] = y[i] + h * (k1 + k2) / 2;  // добавка с полусуммой
        x[i + 1] = x[i] + h;
    }
 	fprintf(out, "%9.3lf %9.3lf\n", x[n], y[n]);
	return;
}

void runge_kutta_4(double (*f)(double, double), double *x, double *y, double h, int n, FILE *out)
{
    for(int i = 0; i < n; i++) {
        fprintf(out, "%9.3lf %9.3lf ", x[i], y[i]);
		fprintf(out, "%9.3lf\n", f1_exac(x[i], y[i]));
        double k1 = (*f)(x[i], y[i]);
        double k2 = (*f)(x[i] + h / 2, y[i] + h * k1 / 2);
        double k3 = (*f)(x[i] + h / 2, y[i] + h * k2 / 2);
        double k4 = (*f)(x[i] + h, y[i] + h * k3);
        y[i + 1] = y[i] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        x[i + 1] = x[i] + h;
    }
    fprintf(out, "%9.3lf %9.3lf\n", x[n], y[n]);
    return;
}

void runge_kutta_sys_2(double (*f)(double, double, double), double (*g)(double, double, double), double *x, double *y, double *z, double h, int n, FILE *out)
{	
    for(int i = 0; i < n; i++) {
		fprintf(out, "%9.3lf %9.3lf %9.3lf\n", x[i], y[i], z[i]);
        double k1 = (*f)(x[i], y[i], z[i]);
        double m1 = (*g)(x[i], y[i], z[i]);
        double k2 = (*f)(x[i] + h, y[i] + h * k1, z[i] + h * m1);
        double m2 = (*g)(x[i] + h, y[i] + h * k1, z[i] + h * m1);
        y[i + 1] = y[i] + h * (k1 + k2) / 2;
        z[i + 1] = z[i] + h * (m1 + m2) / 2;
        x[i + 1] = x[i] + h;
    }
    fprintf(out, "%9.3lf %9.3lf %9.3lf\n", x[n], y[n], z[n]);
	return;
}

void runge_kutta_sys_4(double (*f)(double, double, double), double (*g)(double, double, double), double *x, double *y, double *z, double h, int n, FILE *out)
{
    for(int i = 0; i < n; i++) {
		fprintf(out, "%9.3lf %9.3lf %9.3lf\n", x[i], y[i], z[i]);
        double k1 = (*f)(x[i], y[i], z[i]);
        double m1 = (*g)(x[i], y[i], z[i]);
        double k2 = (*f)(x[i] + h / 2, y[i] + h * k1 / 2, z[i] + h * m1 / 2);
        double m2 = (*g)(x[i] + h / 2, y[i] + h * k1 / 2, z[i] + h * m1 / 2);
        double k3 = (*f)(x[i] + h / 2, y[i] + h * k2 / 2, z[i] + h * m2 / 2);
        double m3 = (*g)(x[i] + h / 2, y[i] + h * k2 / 2, z[i] + h * m2 / 2);
        double k4 = (*f)(x[i] + h, y[i] + h * k3, z[i] + h * m3);
        double m4 = (*g)(x[i] + h, y[i] + h * k3, z[i] + h * m3);
        y[i + 1] = y[i] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        z[i + 1] = z[i] + (h / 6) * (m1 + 2 * m2 + 2 * m3 + m4);
        x[i + 1] = x[i] + h;
    }
	fprintf(out, "%9.3lf %9.3lf %9.3lf\n", x[n], y[n], z[n]);
	return; 
}

double f1(double x, double y) { return (y - y*y) * x; } //(0, 3)

double f1_exac(double x, double y)
{
	double proc = x*x / 2;
	return pow(e, proc) / (pow(e, proc) - 2./3);
}

double f1_sys(double x, double y, double z) { return 2.4 * z - y; }

double f2_sys(double x, double y, double z) { return pow(e, -1. * y) - x + 2.2 * z; }

double test2(double x, double y) { return 3 - y - x; } // (0, 0)

double test2_exac(double x, double y) { return 4 - x - 4*pow(e, -1. * x); }

double test3(double x, double y) { return -1.*y - x*x; } // (0, 10)

double test3_exac(double x, double y) {return -1.*x*x +2*x - 2 + 12*pow(e, -1.*x);}
