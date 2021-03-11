#include <stdio.h>

void mp(int);

int main(void){
	int count = 1;
	mp(count);
	
	return 0;
}

void mp(int count){
	int tmp;
	scanf("%d", &tmp);
	if(tmp == 0) return;
	
	if(count%2 == 1){
		printf("%d ", tmp);
		mp(count+1);
	}
	else{
		mp(count+1);
		printf("%d ", tmp);
	}
}
