#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int M = 2, N = 30; // пункт 2.2 приложение 2
const double pi = 3.1415926535;	

int main(int argc, char **argv)
{
//	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen("wolphram1.txt", "w");
	double q = 1.001 - 2 * M * 0.001;
	int n = N;
	double x = pi/2;
	
	fprintf(out, "{");
	for (int i = 0; i < n; i++) {
		fprintf(out, "{");
		for (int j = 0; j < n; j++) {
			if (i == j) {
				fprintf(out, "%.3lf", pow(q-1, (double)(i+j)));
				if (j != n-1) fprintf(out, ", ");
			} else {
				fprintf(out, "%.3lf", pow(q, (double)(i+j)) + 0.1 * (j - i));
				if (j != n-1) fprintf(out, ", ");
			}	
		}
		fprintf(out, "}");
		if (i != n-1) fprintf(out, ", ");
	}
	fprintf(out, "}");
/*	fscanf(in, "%d", &n);

	fprintf(out, "{");
	for(int i =0; i <n; i++) {
		fprintf(out, "{");
		for (int j = 0; j < n; j++) {
			fscanf(in, "%lf", &x);
			fprintf(out, "%.1lf", x);
			if (j != n-1) fprintf(out, ", ");
		}
		fprintf(out, "}");
		if (i != n-1) fprintf(out, ", ");
	}

	fprintf(out, "}");
*/
	return 0;
}
