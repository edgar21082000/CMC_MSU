#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

enum
{
	FILES = 0, 
	FORMULES = 1,
};


// данные для примера 2
const int M = 2, N = 40; // пункт 2.2 приложение 2
const double pi = 3.1415926535;	

void check_print(double **a, double *x, int n);
void init_matr(FILE *f, double **a, double *x, int n, int mode);
void mul_AX(double **a, double *x, int n);
void mul_AA(double **a, double **b, int n);
void cpy1(double *a, double *b, int n);
void cpy2(double **a, double **b, int n);
void transp(double **At, double **a, int n);
double norm(double *x, int n);
int relax(double **a, double *x, double *f, int n, double eps, double w);



int main(int argc, char **argv)
{
	FILE *fin = fopen(argv[1], "r");
	int n;
	fscanf(fin, "%d", &n);

	int mode; 
	sscanf(argv[2], "%d", &mode);

	if (mode == 1) 
		n = N;
	
	double **A, *x, *f;
	x = calloc(n, sizeof(double));
	f = calloc(n, sizeof(double));
	A = calloc(n, sizeof(double *));

	init_matr(fin, A, f, n, mode);

	double eps, w;
	sscanf(argv[3], "%lf", &eps);
	sscanf(argv[4], "%lf", &w);

	int steps = relax(A, x, f, n, eps, w);
	for(int i = 0; i < n; i++)
		printf("%.6lf ", x[i]);
	printf("  w = %.1lf: iterations = %d\n", w, steps);
	
	return 0;
}

int relax(double **a, double *x, double *f, int n, double eps, double w)
{
    int cnt = 0;
    double **At = calloc(n, sizeof(double *));
	for (int i = 0; i < n; i++)
		At[i] = calloc(n, sizeof(double));
    
	double *x_prev = calloc(n, sizeof(double));
	double *ft = calloc(n, sizeof(double));
    
	transp(At, a, n);
    mul_AA(At, a, n); // A = At * A
    mul_AX(At, f, n); // b = At * b

    do {
        cnt++;
        for(int i = 0; i < n; i++) {
            x_prev[i] = x[i];
        }
        for(int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
               sum += a[i][j] * x[j];
            }

            for (int j = i; j < n; j++) {
               sum += a[i][j] * x_prev[j];
            }

            x[i] = x_prev[i] + w * (f[i] - sum) / a[i][i];
        }

        for(int i = 0; i < n; i++) {
            x_prev[i] = x[i];
        }
        mul_AX(a, x_prev, n); // x_prev = A * x
        for(int i = 0; i < n; i++) {
            x_prev[i] -= f[i];
        }
    } while (norm(x_prev, n) > eps);
    free(At);
	free(ft);
    free(x_prev);
    return cnt;
}

void transp(double **At, double **a, int n)
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			At[i][j] = a[j][i];	
		
}

void cpy1(double *a, double *b, int n)
{
	for(int i = 0; i < n; i++) 
		a[i] = b[i];
}

void cpy2(double **a, double **b, int n)
{
	for(int i = 0; i < n; i++) 
		for(int j = 0; j < n; j++)	
			a[i][j] = b[i][j];
}


void mul_AX(double **a, double *x, int n)
{
	double *res = calloc(n, sizeof(double));
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			res[i] += a[i][j] * x[j];	
		}
	}
	cpy1(x, res, n);
	free(res);
}

void mul_AA(double **a, double **b, int n)
{
	double **res = calloc(n, sizeof(double *));
	for (int i = 0; i < n; i++) 
		res[i] = calloc(n, sizeof(double));
    
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }

	cpy2(b, res, n);
	free(res); 
}

double norm(double *x, int n)
{
	double res = 0. ;
	for (int i = 0; i < n; i++)
		res += x[i] * x[i];
	res = sqrt(res);
	return res;
}



void init_matr(FILE *fin, double **A, double *f, int n, int mode)
{	
	double q = 1.001 - 2 * M * 0.001;

	for (int i = 0; i < n; i++) 
		A[i] = calloc(n, sizeof(double));

	switch (mode) {
		case FILES:
			
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					fscanf(fin, "%lf", &A[i][j]);		
				}
			}
			
			
			for (int i = 0; i < n; i++)
				fscanf(fin, "%lf", &f[i]);
				
			break;
		
		case FORMULES:
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i == j) {
						A[i][j] = pow(q-1, (double)(i+j));
					} else {
						A[i][j] = pow(q, (double)(i+j)) + 0.1 * (j - i);
					}	
				}
			}
			
			double x = pi/2; // случайный параметр для генерация вектора f
			for (int i = 0; i < n; i++)
				f[i] = fabs(x - N/10.) * i * sin(x);
			
			break;
		
		default:
			return;
	}
	
	return;		
}


void check_print(double **A, double *f, int n)
{
	printf("A:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%lf ", A[i][j]);
		}
		printf("\n");
	}
	printf("\nf: ");
	for (int i = 0; i < n; i++)
		printf("%lf ", f[i]);
	printf("\n");
}


