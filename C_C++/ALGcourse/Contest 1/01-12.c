#include <stdio.h>

int main(void){
	int m1 = -10000000, m2=-10000000, m3=-10000000 ,num, N, i;
	scanf("%d", &N);
	
	for(i=0;i<N;i++){
		scanf("%d", &num);
		if(num<m3) continue;
		else{
			if(num<m2) m3 = num;
			else{
				if(num<m1){
					m3 = m2;
					m2 = num;
				}
				else{
					m3 = m2;
					m2 = m1;
					m1 = num;
				}
			}
		}
	}	
	
	printf("%d %d %d", m1, m2, m3);
	return 0;
}
