#include <stdio.h>
#include <stdlib.h>

int main(void){
	int a, *mas, size = 1;
	mas = (int *)malloc(sizeof(int));
	
	
	while(1){
		scanf("%d", &a);
		if(a == 0){
			size--;
			break;
		}
		
		mas[size-1] = a;
		size++;
		mas = realloc(mas, size*sizeof(int));
	}
	
	int cnt = 0;
	for(int i=0; i<size; i++){
		if(mas[i] < mas[size-1])
			cnt++;
	}
	
	free(mas);
	printf("%d", cnt);
	return 0;
}
