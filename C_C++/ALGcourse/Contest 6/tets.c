#include <stdio.h>
void sort(int *, int);

int main(void){
	int arr[] = {3, 4, 9, 5 ,7, 6, 1, 2, 8, 0};
	sort(arr, 10);
	for(int i=0; i<10; i++) printf("%d ", arr[i]);
	
	return 0;
}

void sort(int *a, int r){
	
	int tmp;
    for(int i=0; i<r-1; i++){
        for(int j = i+1; j<r; j++){
            if(a[j] < a[i]){
                tmp = a[j];
                a[j] = a[i];
                a[i] = tmp;
            }
        }
    }
    
    //for(int i=0; i<4; i++) printf("%d ", a[i]);
}
