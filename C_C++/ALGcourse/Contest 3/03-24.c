#include <stdio.h>

int lighten(int N);

int main(void){
	int N; scanf("%d", &N);
	printf("%d", lighten(N));
	return 0;
}

int lighten(int N){
	long long int r, light_count = 0, right_border = 0, f = 0, fl = 1;
	
	for(int k=1; k<=N; k++){
		scanf("%lli", &r);
		if (r==0) continue;
		
		if (r>0){
			if (k>right_border){
				if (k+r<=N){
					light_count += r;
					right_border = k + r;
					//printf("<<1>>\n");
				}
				else{
					light_count += (N - k);
					right_border = N;
					//printf("<<2>>\n");
				}
				fl = 0;
			}
			else{
				if (k+r<=N){
					light_count -= (right_border - k);
					light_count += r;
					right_border = k + r;
					//printf("<<3>>\n");
				}
				else{
					light_count -= (right_border - k);
					light_count += (N - k);
					right_border = N;
					//printf("<<4>>\n");
				}
				fl = 1;
			}
			f = k;
		}
		else{
			r *= -1;
			if (k>right_border){
				if (k-r>f){
					if (k-r<=right_border){
						light_count += r;
						light_count -= ( ( (right_border - f) + r ) - (k - f - 1) );
						//printf("<<5>>\n");
					}
					else{
						light_count += r;
						//printf("<<6>>\n");
					}	 
				}
				else{
					if (right_border > f) light_count -= (right_border - f);
					light_count += (k - f - 1) + (1 - fl);
					//printf("<<7>>\n");
				}
				right_border = k - 1;
				fl = 0;
			}
			else{
				if (k-r>f){
					light_count -= (right_border - k);
					//printf("<<8>>\n");
				}
				else{
					light_count -= (right_border - k);
					light_count += 1 - fl;
					//printf("<<9>>\n");
				}
				
				right_border = k;
				fl = 1;
			}
			f = k;
		}
		//printf("(%d)_light_count = %d f = %d right_border = %d, fl = %d\n", r, light_count, f, right_border, fl);
	}
	return (int)light_count;
}

/* test
	30
	0 0 -3 4 50 3 40 0 0 0 -2 4 0 0 -4 0 0 -3 0 0 -1 0 -5 2 0 0 -2 5 0 -2 
	Yes (23)
	
	30
	0 0 0 0 -7 0 0 0 4 0 0 3 0 0 0 -2 0 0 0 8 40 0 0 0 -3 0 0 0 5 0 0 -1
	Yes	(19)
	
	30
	2 0 -2 2 0 -2 2 0 -2 2 0 -2 2 0 -2 2 0 -2 2 0 -2 2 0 -2 2 0 -2 2 0 -2
	Yes (30)
	
	50
	2 0 0 0 0 3 0 0 4 0 0 0 0 0 50 0 0 0 0 40 0 1 0 0 -1 2 0 0 0 -5 4 0 0 -2 5 0 0 -5 0 0 0 0 4 0 -3 6 0 0 2 0 
	Yes (36)
	
	40
	2 0 -3 0 0 0 4 0 -2 0 0 -1 0 0 -4 0 0 45 0 0 -3 0 0 50 -4 0 0 0 2 0 0 0 0 0 -4 0 0 0 0 1  
	Yes (21)
*/ 
