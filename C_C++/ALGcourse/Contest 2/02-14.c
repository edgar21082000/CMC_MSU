#include <stdio.h>
#include <stdlib.h>

void Sort(int *a, int size);

int main(void){
	int N, b_size, i;
	scanf("%d", &N); 
	b_size = N;
	
	int *res, *buf, *mas;
	
	buf = (int *)malloc((N+1)*sizeof(int));
	mas = (int *)malloc((N+1)*sizeof(int));
	res = (int *)malloc((N+1)*sizeof(int));
	
	for(i=1; i<=N; i++) scanf("%d", &mas[i]);
	for(i=1; i<=N; i++) buf[i] = i;
	
	for(i=1; i<=N; i++){
		if (mas[i] > N-i){
			printf("-1");
			return 0;
		}
		
		res[i] = buf[b_size - mas[i]];
		buf[b_size - mas[i]] = N+1;
		Sort(buf, b_size);
		b_size--;
	}
				
	for(i=1; i<=N; i++) printf("%d ", res[i]);

	free(buf); 
	free(mas); 
	free(res);
	
	return 0;
}

void Sort(int *a, int size){
	int i, j, tmp;
	for(i=1; i<size; i++){
		for(j=1; j<size - i + 1; j++){
			if (a[j] > a[j+1]){
				tmp = a[j+1];
				a[j+1] = a[j];
				a[j] = tmp;
			}
		}
	}
	return ;
}



