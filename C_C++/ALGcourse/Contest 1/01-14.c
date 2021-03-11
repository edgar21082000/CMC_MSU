#include <stdio.h>
#include <limits.h>

int main(void){
	long long int  max1 = INT_MIN, max2 = INT_MIN;
	long long int  min1 = INT_MAX, min2 = INT_MAX;
	
	int N, a, i;
	
	scanf("%d", &N);
	
	for(i=0;i<N;i++){
		scanf("%d", &a);
		
		if(a>=max1){
			max2 = max1;
			max1 = a;
		}
		else if(a>=max2){
			max2 = a;
			
		}
		
		if(a<=min1){
			min2 = min1;
			min1 = a;
			
		}
		else if(a<=min2) min2 = a;
		
	
	}
	
	//printf("%lli  %lli  %lli  %lli\n", min1, min2, max2, max1);
	
	if(min1<=0 && min2<=0){
		if(min1*min2>=max1*max2) {
			printf("%lli %lli", min1, min2);
			return 0;
		}
		else {
			printf("%lli %lli", max2, max1);
			return 0;
		}
	}
	
	else printf("%lli %lli", max2, max1);	
	
	
	return 0;
}
