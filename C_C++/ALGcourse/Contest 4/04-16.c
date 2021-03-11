#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*test
	in :  1111000010101011111000000111110000
	out: 0000001111100001111000010101011111
	
	in : 101010101010101
	out: 010101010101011
*/

int compression(char *, int *);
int redact(int *, int);
int variation_create(int *, int, int *);
int possible_ans_cmp(int *, int, int *, int);
void print(int *, int, int *, int);

int min(int , int);
int abs(int);
void check_print(int *, int);

int main(void){
	char *s;
	s = (char *)malloc(2000001*sizeof(char));
	scanf("%2000000s", s);
	
	int size = min((int)strlen(s), 4000);
	
	int *zero_one_arr, *max_zero_index, zoa, mzi;
	zero_one_arr = (int *)malloc(size*sizeof(int));
	max_zero_index = (int *)malloc(size*sizeof(int));
	
	zoa = compression(s, zero_one_arr); //check_print(zero_one_arr, zoa);
	zoa = redact(zero_one_arr, zoa); //check_print(zero_one_arr, zoa);
	mzi = variation_create(zero_one_arr, zoa, max_zero_index); //check_print(max_zero_index, mzi);
	
	int start_index = possible_ans_cmp(zero_one_arr, zoa, max_zero_index, mzi); //printf("start = %d\n", start_index);
	
	print(zero_one_arr, zoa, max_zero_index, start_index);
	
	free(zero_one_arr);
	free(max_zero_index);
	free(s);
	return 0;
}

int compression(char *s, int *zero_one_arr){
	char cur = s[0];
	
	int i = 1, cur_cnt = 1, zoa = 0, sign;
	if(cur == '0') sign = 1;
	else sign = -1;
	
	while(s[i]){
		while(s[i++] == cur) cur_cnt++;
		zero_one_arr[zoa++] = cur_cnt*sign;
		cur = s[--i];
		sign = sign*(-1);
		cur_cnt = 0;
	}
	
	return zoa;
}

int redact(int *arr, int zoa){
	if((arr[0] > 0) && (arr[zoa-1] > 0)){
		arr[0] += arr[zoa-1];
		zoa--;
		return zoa;
	}
	if((arr[0] < 0) && (arr[zoa-1] < 0)){
		arr[zoa-1] += arr[0];
		for(int i=0; i<zoa-1; i++) arr[i] = arr[i+1];
		zoa--;
		return zoa;
	}
	if(arr[0] < 0){
		int tmp = arr[0];
		for(int i=0; i<zoa-1; i++) arr[i] = arr[i+1];
		arr[zoa-1] = tmp;
	}
	
	return zoa;
}

int variation_create(int *arr, int zoa, int *var){
	int mzi = 0;
	int max_t = arr[0];
	var[mzi++] = 0;
	
	for(int i=1; i<zoa; i++){
		//printf("max = %d | arr[i] = %d | i = %d | mzi = %d| var[mzi -1] = %d\n", max_t, arr[i], i, mzi, var[mzi-1]);
		if(max_t == arr[i]){
			var[mzi++] = i;
		}
		if(max_t < arr[i]){
			max_t = arr[i];
			mzi = 0;
			var[mzi++] = i;
		}
	}
	return mzi;
}

int possible_ans_cmp(int *arr, int zoa, int *var, int mzi){
	int ans_index = 0;
	
	for(int j=1; j<mzi; j++){
		for(int i = 1; i<zoa; i++){
			if(arr[(var[ans_index]+i)%zoa] > arr[(var[j]+i)%zoa]){
				break;
			}
			
			if(arr[(var[ans_index]+i)%zoa] < arr[(var[j]+i)%zoa]){
				ans_index = j;
				break;
			}
		}
	}
	
	return ans_index;
}

void print(int *arr, int zoa, int *var, int st){
	for(int i=0; i<zoa; i++){
		for(int j=0; j<abs(arr[(var[st]+i)%zoa]); j++){
			//printf("index = %d | kol = %d\n", var[st]+i)%zoa)
			if((var[st]+i)%2 == 0) 
				printf("0");
			else
				printf("1");
		}
	}
	
	return ;
}

int min(int a, int b){
	return a > b ? b : a;
}

int abs(int a){
	return a >= 0 ? a : -a; 
}

void check_print(int *a, int N){
	for(int i = 0; i<N; i++) printf("%d ", a[i]);
	printf("\n");
}
