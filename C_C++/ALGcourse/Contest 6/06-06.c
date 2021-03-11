#include <stdio.h>
#include <stdlib.h>

typedef struct list{
	int x;
	struct list *next;
}list;

list * read(FILE *, list *);
void print(FILE *, list *, list *);
void clear(list *);
void check_print(list *);

int main(void){
	FILE *A, *B;
	A = fopen("input.txt", "r");
	B = fopen("output.txt", "w");
	
	list *first, *second;
	first = calloc(1, sizeof(list));
	second = calloc(1, sizeof(list));
	
	first = read(A, first);
	second = read(A, second); 
	
	print(B, first, second);
	
	fclose(A); 
	fclose(B);
	clear(first); 
	clear(second);
	
	return 0;
}

list * read(FILE *fp, list *sp){
	int num;
	list *head = sp;
	while(1){
		fscanf(fp, "%d", &num);
		if(num == -1){
			sp->x = -1;
			break;
		}
		else{
			sp->x = num;
			sp->next = calloc(1, sizeof(list));
			sp = sp->next;
		}	
	}
	
	return head;
}

void print(FILE *fp, list *first, list *second){
	list *tmp = second;
	int flag;
	
	while(first->x != -1){
		flag = 1;
		while(tmp->x != -1){
			if (first->x == tmp->x){
				flag = 0;
				break;
			}
			tmp = tmp->next;
		}
		if(flag)
			fprintf(fp, "%d ", first->x);
		
		first = first->next;
		tmp = second;	
	}
}

void clear(list *t){
	list *tmp = t;
	while(t){
		tmp = t->next;
		free(t);
		t = tmp; 
	}	
}

void check_print(list *sp){
	list *tmp = sp;
	while(tmp->x != -1){
		printf("%d ", tmp->x);
		tmp = tmp->next;
	}
}
