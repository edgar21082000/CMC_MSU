#include <stdio.h>
#include <stdlib.h>

int main(void){
	int arr[] = {4, 36, 12, 3, -1, -1, 0, -1, -1, 2, 48, 24, 1, -1, -1};	
	FILE *A; 
	A = fopen("input.bin", "wb");
	fwrite(arr, 4, 15, A);
	
	fclose(A);
	return 0;
}
