#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void Hex_bin(char a[5], int* N);
void Bin_hex(char a[5], int* N);
void transposition(int A[4][4]);

int main(void){
	char in[5]; scanf("%s", in);
    int* N; N=(int *)malloc(16*sizeof(int));
	
	Hex_bin(in, N);
	
	int i, j; //for(i=0; i<16; i++) printf("%d ", N[i]);
	int A[4][4];
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			A[i][j] = N[15-i*4-j];
		}
	}
	
	transposition(A);	
	
	/*printf("\n\n\n");
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}*/
	
	int* K; K=(int *)malloc(16*sizeof(int));
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			K[15-4*i-j] = A[i][j];
		}
	}
	
	char out[5];
	Bin_hex(out, K);
	
	printf("%s", out);
	
	
	return 0;
}


void Hex_bin(char a[5], int* N){
	//int* N; N=(int *)malloc(16*sizeof(int));
	int i;
	for(i=3;i>=0;i--){
		if(a[i] == '0') {N[4*i+0] = 0; N[4*i+1] = 0; N[4*i+2] = 0; N[4*i+3] = 0;}
		if(a[i] == '1') {N[4*i+0] = 0; N[4*i+1] = 0; N[4*i+2] = 0; N[4*i+3] = 1;}
		if(a[i] == '2') {N[4*i+0] = 0; N[4*i+1] = 0; N[4*i+2] = 1; N[4*i+3] = 0;}
		if(a[i] == '3') {N[4*i+0] = 0; N[4*i+1] = 0; N[4*i+2] = 1; N[4*i+3] = 1;}
		if(a[i] == '4') {N[4*i+0] = 0; N[4*i+1] = 1; N[4*i+2] = 0; N[4*i+3] = 0;}
		if(a[i] == '5') {N[4*i+0] = 0; N[4*i+1] = 1; N[4*i+2] = 0; N[4*i+3] = 1;}
		if(a[i] == '6') {N[4*i+0] = 0; N[4*i+1] = 1; N[4*i+2] = 1; N[4*i+3] = 0;}
		if(a[i] == '7') {N[4*i+0] = 0; N[4*i+1] = 1; N[4*i+2] = 1; N[4*i+3] = 1;}
		if(a[i] == '8') {N[4*i+0] = 1; N[4*i+1] = 0; N[4*i+2] = 0; N[4*i+3] = 0;}
		if(a[i] == '9') {N[4*i+0] = 1; N[4*i+1] = 0; N[4*i+2] = 0; N[4*i+3] = 1;}
		if(a[i] == 'a') {N[4*i+0] = 1; N[4*i+1] = 0; N[4*i+2] = 1; N[4*i+3] = 0;}
		if(a[i] == 'b') {N[4*i+0] = 1; N[4*i+1] = 0; N[4*i+2] = 1; N[4*i+3] = 1;}
		if(a[i] == 'c') {N[4*i+0] = 1; N[4*i+1] = 1; N[4*i+2] = 0; N[4*i+3] = 0;}
		if(a[i] == 'd') {N[4*i+0] = 1; N[4*i+1] = 1; N[4*i+2] = 0; N[4*i+3] = 1;}
		if(a[i] == 'e') {N[4*i+0] = 1; N[4*i+1] = 1; N[4*i+2] = 1; N[4*i+3] = 0;}
		if(a[i] == 'f') {N[4*i+0] = 1; N[4*i+1] = 1; N[4*i+2] = 1; N[4*i+3] = 1;}
		
	}
	//for(i=0; i<16; i++) printf("%d ", N[i]);
	return ;
}

void transposition(int A[4][4]){
	int i, j, tmp;
	for(i=0;i<4;i++){
		for(j=i;j<4;j++){
			tmp = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = tmp;
		}
	}
	return ;	
}

void Bin_hex(char a[5], int* N){
	int i;
	for(i=3;i>=0;i--){
		if(N[4*i+0] == 0 && N[4*i+1] == 0 && N[4*i+2] == 0 && N[4*i+3] == 0) a[i] = '0';
		if(N[4*i+0] == 0 && N[4*i+1] == 0 && N[4*i+2] == 0 && N[4*i+3] == 1) a[i] = '1';
		if(N[4*i+0] == 0 && N[4*i+1] == 0 && N[4*i+2] == 1 && N[4*i+3] == 0) a[i] = '2';
		if(N[4*i+0] == 0 && N[4*i+1] == 0 && N[4*i+2] == 1 && N[4*i+3] == 1) a[i] = '3';
		if(N[4*i+0] == 0 && N[4*i+1] == 1 && N[4*i+2] == 0 && N[4*i+3] == 0) a[i] = '4';
		if(N[4*i+0] == 0 && N[4*i+1] == 1 && N[4*i+2] == 0 && N[4*i+3] == 1) a[i] = '5';
		if(N[4*i+0] == 0 && N[4*i+1] == 1 && N[4*i+2] == 1 && N[4*i+3] == 0) a[i] = '6';
		if(N[4*i+0] == 0 && N[4*i+1] == 1 && N[4*i+2] == 1 && N[4*i+3] == 1) a[i] = '7';
		if(N[4*i+0] == 1 && N[4*i+1] == 0 && N[4*i+2] == 0 && N[4*i+3] == 0) a[i] = '8';
		if(N[4*i+0] == 1 && N[4*i+1] == 0 && N[4*i+2] == 0 && N[4*i+3] == 1) a[i] = '9';
		if(N[4*i+0] == 1 && N[4*i+1] == 0 && N[4*i+2] == 1 && N[4*i+3] == 0) a[i] = 'a';
		if(N[4*i+0] == 1 && N[4*i+1] == 0 && N[4*i+2] == 1 && N[4*i+3] == 1) a[i] = 'b';
		if(N[4*i+0] == 1 && N[4*i+1] == 1 && N[4*i+2] == 0 && N[4*i+3] == 0) a[i] = 'c';
		if(N[4*i+0] == 1 && N[4*i+1] == 1 && N[4*i+2] == 0 && N[4*i+3] == 1) a[i] = 'd';
		if(N[4*i+0] == 1 && N[4*i+1] == 1 && N[4*i+2] == 1 && N[4*i+3] == 0) a[i] = 'e';
		if(N[4*i+0] == 1 && N[4*i+1] == 1 && N[4*i+2] == 1 && N[4*i+3] == 1) a[i] = 'f';
	}	
	return ;
}
