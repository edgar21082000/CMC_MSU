#include <stdio.h>
#include <math.h>

int maxi(int, int);
int mini(int, int);
int absl(int);

int main(void){
	int a, b;
	scanf("%d%d", &a, &b);
	int x = maxi( absl(a), absl(b));
	int y = mini( absl(a), absl(b));
	
	int d = x -y;
	
	if(d%2 == 0) printf("%d", 2*y + 2*d);
	else printf("%d", 2*y + 2*d - 1);
	
	
	return 0;
}



int maxi(int a, int b){
	if(a>=b) return a;
	else return b;
}

int mini(int a, int b){
	if(a<=b) return a;
	else return b;
}

int absl(int a){
	if(a>=0) return a;
	else return(-1)*a;
}
