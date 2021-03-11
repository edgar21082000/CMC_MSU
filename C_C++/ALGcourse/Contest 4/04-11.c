#include <stdio.h>
#include <string.h>
#include <math.h>

int is_digit(char a);

int abs(int a);

void print(char num1[], int k1, char num2[], int k2, char op);

int main(void){
	char s[2001];
	fgets(s, 2000, stdin);
	s[strlen(s)-1] = '\0';
	
	char num1[12], num2[12], op;
	int i = 0, k1 = 0, k2 = 0, flag = 0, r1 = 0, r2 = 0, exit = 0;
	
	while(s[i]!='\0'){
		
		if (exit == 1) break;
		
		if (flag == 0)
			while(1){
				if(s[i]=='\0'){
					exit = 1;
					break;
				}
				
				if(is_digit(s[i])){
					num1[k1] = s[i]; num1[k1+1] = '\0';
					k1++;
					i++;
					r1 = 1;
				}
				else{
					if(r1 == 1){
						flag = 1;
						break;
					}
					else{
						i++;
						continue;
					}
				}
			}
		
		while(1){
			if(s[i]=='\0'){
				exit = 1;
				break;
			}
			
			if( (flag == 1) && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' ) ){
				op = s[i];
				flag = 2;
				i++;
				break;
			}
			else{
				i++;
				break;
			}
		}
		
		if (flag == 2)
			while(1){
				if(s[i]=='\0'){
					exit = 1;
					if (r2 == 1) flag = 3;
					break;
				}
				
				if(is_digit(s[i])){
					num2[k2] = s[i]; num2[k2+1] = '\0';
					k2++;
					i++;
					r2 = 1;
				}
				else{
					if(r2 == 1){
						flag = 3;
						break;
					}
					else{
						i++;
						break;
					}
				}
			}
	
		if (flag == 3)
			print(num1, k1, num2, k2, op);
		
		k1 = 0;
		k2 = 0;
		r1 = 0;
		r2 = 0;
		
		if ((flag == 3) && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' )){
			flag = 1;
			k1 = k2;
		}
		else
			flag = 0;
		
	}
	
	return 0;
}

void print(char num1[], int k1, char num2[], int k2, char op){
	int l1 = strlen(num1) - 1;
	int l2 = strlen(num2) - 1;
	
	int n1 = 0, n2 = 0, res = 0;
	
	for(int i = 0; i<=l1; i++) n1 += pow(10, l1 - i)*(int)(num1[i] - '0');
	for(int i = 0; i<=l2; i++) n2 += pow(10, l2 - i)*(int)(num2[i] - '0');
	
	for(int i = 0; i<=l2+1; i++) num1[i] = num2[i];
	
	if(op == '+') res = n1 + n2;
	if(op == '-') res = n1 - n2;
	if(op == '*') res = n1 * n2;
	if(op == '/') {
		if(n2 == 0) res = 120001; 
		else res = n1 / n2;	
	}
	
	if(abs(res) <= 120000) printf("%d %c %d = %d\n", n1, op, n2, res);	
}

int is_digit(char a){
	if('0' <= a && a <= '9') return 1;
	return 0;
}

int abs(int a){
	if(a <= 0 ) return -a;
	return a;
}
