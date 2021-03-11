#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string{
	char word[20][101];
}mt;

int add(char *, mt *, unsigned int *, unsigned int);
void sort(int, mt *, int);
void print(FILE *, mt *, int, int);
int is_digit(char);

int main(void){
	FILE *A, *B;
	A = fopen("input.txt", "r");
	B = fopen("output.txt", "w");
	
	char *buf;
	buf = (char *)malloc(100*21*sizeof(char));
	
	mt *str;
	unsigned int s_kol = 64, r = 0;
	str = (mt *)malloc(s_kol*sizeof(mt));
	
	int key, col_num = 0;
	fscanf(A, "%d\n", &key); // \n - ???
	
	while(fgets(buf, 2100, A)){
		if(buf[strlen(buf)-1] == '\n')
			buf[strlen(buf)-1] = '\0';
		col_num = add(buf, str, &s_kol, r);
		r++;	
	}
	
	/*
	//---------print------------------------
	for(int k=0; k<r; k++){
		for(int j=0; j<col_num; j++){
			printf("%s ", str[k].word[j]);
		}
		printf("\n");
	}
	//--------------------------------------
	*/
	
	sort(key, str, r);
	
	print(B, str, r, col_num);
	
	
	fclose(A);
	fclose(B);
	free(buf);
	return 0;
}

int add(char *buf, mt *str, unsigned int *s_kol, unsigned int r){
	if(r == *s_kol){
		*s_kol <<= 1;
		str = realloc(str, (*s_kol) * sizeof(mt));
	}
	
	char tmp[101];
	int len = strlen(buf), t_i = 0, semi = 0, flag = 1;
	for(int i=0; i<=len; i++){
		if(buf[i] == ';' || buf[i] == '\0'){
			strcpy(str[r].word[semi], tmp);
			t_i = 0;
			semi++;
			continue; // word without ; -- else the word include ;
		}
		
		if(buf[i] == '"') 
			flag *= -1;
		
		
		if(flag == 1)
			if(buf[i] == ' ') continue;
		
		tmp[t_i++] = buf[i];
		tmp[t_i] = '\0';
	}

	
	return semi;
}

void sort(int key, mt *str, int r){
	mt tmp; 
	int tnum;
	if(is_digit(str[0].word[key][strlen(str[0].word[key])-1])){  //////??????????????
		int a[r];
		for(int i=0; i<r; i++)
			a[i] = atoi(str[i].word[key]);
		
		for(int i=0; i<r-1; i++){
        	for(int j = i+1; j<r; j++){
            	if(a[j] < a[i]){
                	tmp = str[j];
					str[j] = str[i];
					str[i] = tmp;
					
					tnum = a[j];
					a[j] = a[i];
					a[i] = tnum;
            	}
        	}
    	}
	}
	
	else{
		for(int i=0; i<r-1; i++){
    		for(int j = i+1; j<r; j++){
        		if(strcmp(str[j].word[key], str[i].word[key]) < 0){ 
            		//printf("%s - %s\n", str[j].word[key], str[i].word[key]);
            		tmp = str[j];
					str[j] = str[i];
					str[i] = tmp;	
            	}
        	}
    	}	
	}
	
	//for(int k=0; k<r; k++) printf("%s\n", str[k].word[key]);
}

void print(FILE *fp, mt *str, int r, int col_num){
	for(int i=0; i<r; i++){
		for(int j=0; j<col_num; j++){
			fprintf(fp, "%s", str[i].word[j]);
			if(j != col_num-1)
				fprintf(fp, ";");
		}
		fprintf(fp, "\n");
	}
}

int is_digit(char a){
	if(a >= '0' && a <= '9') return 1;
	return 0;
}
