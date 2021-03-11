#include <stdio.h>
int sort(int, int, int);

int main(void){
	int x, y, z;
	scanf("%d%d%d", &x, &y, &z);
	
	int ans = sort(x, y, z);
	
	printf("%d", ans);
	
	return 0;
}

int sort(int x, int y, int z)
{
	int a[3];
	a[0] = x; a[1] = y; a[2] = z;
	int tmp;
	
	for(int i=0; i<3; i++){
		for(int j = 1; j < 3-i; j++){
			if (a[j] < a[j-1]){
				tmp = a[j];
				a[j] = a[j-1];
				a[j-1] = tmp;	
			}
			
		}
	}
	
	return a[1];
}
