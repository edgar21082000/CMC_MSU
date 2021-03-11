#include <stdio.h>
#include <stdlib.h>

int check(FILE *, int);
int ans_key_maker(int *, int);
 
int main(void){
	FILE *A, *B;
	A = fopen("input.bin", "rb");
	B = fopen("output.bin", "wb");
	
	fseek(A, 0, SEEK_END);
	long size = ftell(A);
	fseek(A, 0, SEEK_SET);
	
	size_t count = size/sizeof(int);
	
	int ans = check(A, count);
	//printf("%d\n", ans);
	fwrite(&ans, sizeof(int), 1, B);
	
	fclose(A);
	fclose(B);	
	return 0;
}
 
int check(FILE *fp, int count){
	if(count == 0) return 0;
	if(count == 1) return 1;
	
	int *arr; 
	arr = (int *)malloc(count*sizeof(int));
	fread(arr, sizeof(int), count, fp);
	//for(int k=0; k<count; k++) printf("%d ", arr[k]); printf("\n");
	int i, ans_key, head, son1, son2;
	
	ans_key = ans_key_maker(arr, count);
		
	i = 0;
	while(2*i+1 < count){
		head = ans_key*arr[i];
		son1 = ans_key*arr[2*i+1];
		if(2*i+2 >= count) 
			son2 = head;
		else
			son2 = ans_key*arr[2*i+2];
		//printf("%d) %d_%d %d_%d\n", ans_key, head, son1, head, son2);
		if(head > son1 || head > son2){
			free(arr);
			return 0;
		}
		
		i++;		
 	}
 	free(arr);
 	return ans_key;
}

int ans_key_maker(int *arr, int n){
	int min = arr[0];
	for(int i=0; i<n; i++)
		if(arr[i]<min)
			return -1;
	return 1;
}
