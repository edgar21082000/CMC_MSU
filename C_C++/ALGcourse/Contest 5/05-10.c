#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_digit(char);
int min(int, int);
int max(int, int);
void read(char *, int *, int *, int *, char *);
void calculate(int *, int *, int *, int *, char);
int plus(int *, int *, int *, int*);
int minus(int *, int *, int *, int*);
int check_bigger(int *, int *, int *);
int multiply(int *, int *, int *, int*);
void print(int *, int);
void check_print(int *, int);

int main(void){
	int *a, *b, *len, *c;
	char op, *s;
	s = (char *)malloc(20002*sizeof(char));
	a = (int *)calloc(10000, sizeof(int));
	b = (int *)calloc(10000, sizeof(int));
	c = (int *)calloc(20000, sizeof(int));
	len = (int *)calloc(3, sizeof(int));
	
	read(s, a, b, len, &op);	 //printf("%c\n", op); check_print(a, len[0]); check_print(b, len[1]);
	calculate(a, b, c, len, op); 
	
	free(s);
	free(a);
	free(b);
	free(c);
	free(len);
	return 0;
}

void read(char *s, int *a, int *b, int *len, char *op){
	scanf("%20001s", s);
	int lgh = strlen(s);
	int flag = 0;
	
	for(int i = lgh-1; i>=0; i--){
		if(flag == 0){
			if(is_digit(s[i]))
				b[len[1]++] = s[i] - '0';
			else{
				*op = s[i];
				flag = 1;
			}
		}
		else
			a[len[0]++] = s[i] - '0';	
	}
}

void calculate(int *a, int *b, int *c, int *len, char op){
	if(op == '+') len[2] = plus(a, b, c, len);
	else if(op == '-') len[2] = minus(a, b, c, len);
	else if(op == '*') len[2] = multiply(a, b, c, len);
	
	print(c, len[2]);
	return ;
}

int plus(int *a, int *b, int *c, int *len){
	int ans_len = max(len[0], len[1]) + 1;
	
	for(int i=0; i<ans_len; i++){
		c[i] += (a[i] + b[i]);
		if(c[i] > 9){
			c[i+1]++;
			c[i] -= 10;
		}
	}
	
	while(c[ans_len-1] == 0) ans_len--;
		
	return ans_len;
}

int minus(int *a, int *b, int *c, int *len){
	int ans_len = max(len[0], len[1]);
	
	int key = check_bigger(a, b, len);
	
	if(key == 1){
		for(int i=0; i<ans_len; i++){
			c[i] += (a[i] - b[i]);
			if(c[i] < 0){
				c[i+1]--;
				c[i] += 10;
			} 
		}
		while(c[ans_len-1] == 0){
			ans_len--;
			if(ans_len == 0)
				break;
		}
	}
	else{
		for(int i=0; i<ans_len; i++){
			c[i] += (b[i] - a[i]);
			if(c[i] < 0){
				c[i+1]--;
				c[i] += 10;
			}
		}
		while(c[ans_len-1] == 0){
			ans_len--;
			if(ans_len == 0)
				break;
		}
		if(ans_len != 0)
			c[ans_len-1] *= key;
	}
	
	return ans_len;
}

int check_bigger(int *a, int *b, int *len){
	if(len[0] > len[1])	
		return 1;
	else if(len[0] < len[1])
		return -1;
	else if(len[0] == len[1]){
		for(int i = len[0]-1; i>=0; i--){
			if(a[i] > b[i])	
				return 1;
			if(a[i] < b[i])
				return -1;
		}
	}
	
	return 0;
}

int multiply(int *a, int *b, int *c, int *len){
	int ans_len = len[0] + len[1];
	
	/*for(int i=0; i<len[0]; i++){
		for(int j=0; j<len[1]; j++){
			c[i+j] += (a[i] * b[j]);
			if(c[i+j] > 9){
				c[i+j+1] += (c[i+j]/10);
				c[i+j] %= 10;
			}
		}
	}*/
	for(int i=0; i<len[0]; i++){
		for(int j=0; j<len[1]; j++){
			c[i+j] += (a[i] * b[j]);
		}
	}
	
	for(int i=0; i<ans_len; i++){
		if(c[i]>9){
			c[i+1] += c[i]/10;
			c[i] %= 10; 
		}
	}
	
	while(c[ans_len-1] == 0){
			ans_len--;
			if(ans_len == 0)
				break;
		}

	return ans_len;
}

void print(int *c, int ans_len){
	if(ans_len == 0)	
		printf("0");
	else
		for(int i = ans_len-1; i>=0; i--)
			printf("%d", c[i]);
}

int is_digit(char a){
	if('0' <= a && a <= '9') return 1;
	return 0;
}

int min(int a, int b){
	return a >= b ? b : a;
}

int max(int a, int b){
	return a >= b ? a : b;
}

void check_print(int *a, int len){
	for(int i=len-1; i>=0; i--){
		printf("%d", a[i]);	
	}
	printf("--%d\n", len);
}
