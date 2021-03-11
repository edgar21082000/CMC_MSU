#include <stdio.h>
#include <stdlib.h>

int main(void){
	int *m, kb = 1;
	int num, z;
	scanf("%d %d", &num, &z);
	
	
	//--------������� ����� �������� ���--------
	int mtmp = 1;
	while(num >= mtmp){
		kb++;
		mtmp <<= 1;
	}
	kb--;
	mtmp>>=1;
	printf("%d\n", kb);
	//-------------------
	
	//-----�������� ������� ������� �����-----
	m = (int *)malloc(kb*sizeof(int));
	for(int i = 0; i < kb; i++){
		m[i] = (1<<i);
	}
	for(int i = 0; i < kb; i++) printf("%d ", m[i]);
	printf("\n");
	//---------------------------------------------
	
	
	
	//----������� ��������----------
	int z_count, num_count = 0;
	for(num; num>=1; num--){// num - ������� ����������� �����
		z_count = 0;
		
		//printf("num = %d\n", num);
		
		if ( (num & m[kb-1]) == 0) kb--; // �������� �� ��, �������� �� ��� ������� ��� ��������
		
		for(int j = kb-1; j>=0; j--){
			if ( (num & m[j]) == 0) z_count++; //printf(" '0' ");
		    if (z_count > z) break;
		}
		
		//printf("z_count = %d\n\n", z_count);
		
		if(z_count == z) num_count++;
	}
	
	printf("%d ", num_count);
	
	return 0;
}
