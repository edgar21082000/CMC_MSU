#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum
{
	FILES = 0, 
	FORMULES = 1,
	WP = 1,
	DET = 1 << 1,
	DISCRP = 1 << 2,
	REV = 1 << 3,
	COND = 1 << 4,
};

int flags =  WP | COND | DET | DISCRP | REV;

// данные для примера 2
const int M = 2, N = 40; // пункт 2.2 приложение 2
const double pi = 3.1415926535;	

void check_print(double **a, double *x, int n);
void init_matr(FILE *f, double **a, double *x, int n, int mode);
void gauss_mod(double **a, double *x, double *f, int n);
double *mul_matr(double **a, double *x, int n);
double **copy_1(double **a, double **,  int n);
double *copy_2(double *f, double *, int n);
double **create_rev(double **rev, int n);
double norm(double **a, int n);
int max_replace(double **a, double *b, int n, int i, double **rev);

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
//check_print(A, f, n);
	gauss_mod(A, x, f, n) ;
//check_print(A, x, n);
	
	
	return 0;
}

void gauss_mod(double **a, double *x, double *f, int n)
{
	int i, j, k , m, replace_cnt = 0;
	double first, determinant = 1. , cond_num = 0. , **a_cpy, **rev, *f_cpy;
	
	if (flags & DET)
		printf("DET - ON\n");	

	if (flags & WP)
		printf("WP - ON\n");	
	
	if (flags & DISCRP) {
		printf("DISCRP - ON\n");
		a_cpy = copy_1(a_cpy, a, n);
		f_cpy = copy_2(f_cpy, f, n);
	}
	
	if (flags & COND) {
		printf("COND - ON\n");
		cond_num += norm(a, n); 
	}

	if ((flags & REV) || (flags & COND)) {
		if (flags & REV) 
			printf("REV - ON\n");
		rev = create_rev(rev, n);
	}

	printf("\n");

	for (i = 0; i < n; i++) {
		if (flags & WP) // fkag WP - it's gauss with a principal element
			replace_cnt += max_replace(a, f, n, i, rev); 
	
		for (j = i; j < n; j++) { // делим строку на первый строки (приводим к единице первый эл)
			if (a[j][i] == 0) first = 1;
			else first = a[j][i];
	
			for (k = 0; k < n; k++) // делим на старший элемент
				a[j][i+k] /= first;
			
			if ((flags & REV) || (flags & COND)) 
				for (int v = 0; v < n; v++)
					rev[j][v] /= first;
			
			f[j] /= first;
	
			if (flags & DET) // паралеллльное вычисление определителя)
				determinant *= first;
		}
		
		for (m = i+1; m < n; m++){ // вычитаем строки друг из друга
			if (a[m][i] == 0) continue;
			
			for (k = 0; k < n-i; k++) 
				a[m][k+i] -= a[i][i+k];				
			
			if ((flags & REV) || (flags & COND)) // работаетм с флагом для -1 матрицы
				for(int v = 0; v < n; v++)					 
					rev[m][v] -= rev[i][v];	

			f[m] -= f[i]; // и столбец значений тоже вычитаем (для гауса)
		}
	}

	for (int g = n-1; g >= 0; g--) { // обратный ход метода гауса
		for(int h = g - 1; h >= 0; h--) {
			f[h] -= f[g]*a[h][g];

			if((flags & REV) || (flags & COND)) 
				for(int v = 0; v < n; v++) 
					rev[h][v] -= rev[g][v] * a[h][g];							

			a[h][g] -= a[g][g] * a[h][g]; // как будто бы вычли 
		}

		x[g] = f[g];
	}


	printf("x: ");
	for(int h = 0; h < n; h++)
		printf("%lf ", x[h]);
	printf("\n");

	determinant *= pow(-1., replace_cnt); // если была перестановка строк
	if (flags & DET) 
		printf("Determinant = %lf\n", determinant);
		
	if (flags & DISCRP) { // считаем невязку
		double *res = mul_matr(a_cpy, x, n);
		double dis = 0.;
		for (int h = 0; h < n; h++)
			dis += (f_cpy[h]-res[h]) * (f_cpy[h]-res[h]); 
		dis = sqrt(dis);
		printf("Discrepancy = %lf\n", dis);
	}
	
	if (flags & COND) {
		cond_num += norm(rev, n);
		printf("Condition number: %lf\n", cond_num);
	}
	if (flags & REV) {
		printf("Revers:\n");
		for(int g = 0; g < n; g++){
			for(int h = 0; h< n; h++){
				printf("%lf ", rev[g][h]);
			}
			printf("\n");
		}
	}	
	
	return ;
}

double *mul_matr(double **a, double *x, int n)
{
	double *res = calloc(n, sizeof(double));
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			res[i] += a[i][j] * x[j];	
		}
	}
	return res;
}

int max_replace(double **a, double *b, int N, int i, double **rev)
{
	int k, j;
	double max = fabs(a[i][i]);
	int tmp = 0;
	
	for (k = i+1; k < N; k++){ 
		if(fabs(a[k][i]) > max){
			max = fabs(a[k][i]);
			tmp = k; 
		}
	}
	
	if (tmp == 0) return 0;
	
	double t;
	for(j = 0; j < N; j++){
		t = a[i][j];
		a[i][j] = a[tmp][j];
		a[tmp][j] = t;
		
		if (flags & REV) {
			t = rev[i][j];
			rev[i][j] = rev[tmp][j];
			rev[tmp][j] = t;
		}
	}
	
	t = b[i];
	b[i] = b[tmp];
	b[tmp] = t;
	
	return 1;
}

double **copy_1(double **res, double **a, int n)
{
	res = calloc(n, sizeof(double *));
	for (int h = 0; h < n; h++) 
		res[h] = calloc(n, sizeof(double));
		
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res[i][j] = a[i][j];
			
	return res; 
}

double *copy_2(double *res, double *f, int n)
{
	res = calloc(n, sizeof(double));
	for (int i = 0; i < n; i++)
		res[i] = f[i];
	return res;
}

double **create_rev(double **rev, int n)
{
	rev = calloc(n, sizeof(double));
	for (int i = 0; i < n; i++)
		rev[i] = calloc(n, sizeof(double));
	for (int i =0; i < n; i++)
		rev[i][i] = 1. ;

	return rev;
}

double norm(double **a, int n)
{
	double res = 0. ;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			res += a[i][j] * a[i][j];
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


