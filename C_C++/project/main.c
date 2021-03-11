#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "library.h"

//extern int iterations;


int main(int argc, char* argv[])
{
	double a = -5., b = 5.	;
	double eps1 = 0.001, eps2 = 0.0001;
	double x12, x13, x23, S1, S2, S3;
	
	
	int i=1;
	int a1, a2;
	double A, B, eps;
	
	
	
	{// parametrs
		if((argc>1) && !strcmp(argv[i], "-help"))
		{
			printf("	HELP	\n");
			printf("-solutions: show the roots of function\n");
			printf("-root: show solution of two function\n");
			printf("-integral: show integral of function\n");
			printf("-iterations: show how many steps makes aproximate solution algoritm\n");
			printf("\n");
			return 0;
		}
		
		if((argc>1) && !strcmp(argv[i], "-root"))
		{
			a1 = atoi(argv[i+1]); // number of rist function
			a2 = atoi(argv[i+2]); // number of second function
			A = atof(argv[i+3]); // lower limit
			B = atof(argv[i+4]); // upper limit
			eps = atof(argv[i+5]); // eps
			#ifdef hord
			if( (a1&a2) == 0) // f1 and f2
				printf("x12 = %lf\n",  root_secant_method(f1, f2, A, B, eps));
			if( (a1&a2) == 1) // f1 and f3
				printf("x13 = %lf\n",  root_secant_method(f1, f3, A, B, eps));
			if( (a1&a2) == 2) // f2 anf f3
				printf("x23 = %lf\n",  root_secant_method(f2, f3, A, B, eps));
			#endif
			
			#ifdef newton
			if( (a1&a2) == 0) //f1 and f2
				printf("x12 = %lf\n",  root_newton_method(f1, f2, df1, df2, A, B, eps));
			if( (a1&a2) == 1) // f1 and f3
				printf("x13 = %lf\n",  root_newton_method(f1, f3, df1, df3, A, B, eps));
			if( (a1&a2) == 2) // f2 and f3
				printf("x23 = %lf\n",  root_newton_method(f2, f3, df2, df3, A, B, eps));
			#endif
			return 0;
		}
		
		if((argc>1) && !strcmp(argv[i], "-integral"))
		{
			a1 = atoi(argv[i+1]);
			A = atof(argv[i+2]);
			B = atof(argv[i+3]);
			eps = atof(argv[i+4]);
			if(a1 == 1)
				printf("Integral f1 = %lf\n", integral(f1, A, B, eps));
			if(a1 == 2)
				printf("Integral f2 = %lf\n", integral(f2, A, B , eps));
			if(a1 == 3)
				printf("Integral f3 = %lf\n", integral(f3, A, B, eps));	
			
			return 0;
		}
		
		{ // main task solution
			#ifdef hord
			x12 = root_secant_method(f1, f2, a, b, eps1);
			x13 = root_secant_method(f1, f3, a, b, eps1);
			x23 = root_secant_method(f2, f3, a, b, eps1);
			#endif
			
			#ifdef newton
			x12 = root_newton_method(f1, f2, df1, df2, a, b, eps1); 
			x13 = root_newton_method(f1, f3, df1, df3, a, b, eps1); 
			x23 = root_newton_method(f2, f3, df2, df3, a, b, eps1);
			#endif
			S1 = integral(f1, x13, x12, eps2); 
			S2 = integral(f2, x23, x12 , eps2);
			S3 = integral(f3, x13, x23, eps2);
		}	
		
		if((argc>1) && !strcmp(argv[i], "-solutions"))
		{
			printf("roots: x12 = %lf; x13 = %lf; x23 = %lf\n", x12, x13, x23);
			if(argc>2)
			{	
				if(!strcmp(argv[i+1], "-iterations"))
				{
					printf("iterations: %d \n", iterations);
				}
			}
		}
		if((argc>1) && !strcmp(argv[i], "-iterations"))
		{
			printf("iterations: %d \n", iterations);
			if(argc>2)
			{
				if(!strcmp(argv[i+1], "-solutions"))
				{
					printf("roots: x12 = %lf; x13 = %lf; x23 = %lf\n", x12, x13, x23);
				}
			}
		}
	}
	
 	printf("S = %lf\n", S1 - S2 - S3);
	
	return 0;
}

