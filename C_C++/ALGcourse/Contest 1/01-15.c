#include <stdio.h>

int sgn(int);

int main(void){
	int x1, y1, x2, y2, x3, y3, N, sign, sign_t, i;
	int x1_, y1_, x2_, y2_, a1, a2, b1, b2;
	scanf("%d", &N);
	
	scanf("%d %d", &x1, &y1);
	scanf("%d %d", &x2, &y2);
	scanf("%d %d", &x3, &y3);
	
	x1_ = x1; y1_ = y1; // ���������� ��������� 2 �����
	x2_ = x2; y2_ = y2;// ����� ����� ����� ������������ ���������� ������� � ������
	
	a1 = x2 - x1; a2 = y2 - y1; // ���������� ������� �������
	b1 = x3 - x2; b2 = y3 - y2;// ���������� ������� �������
	
	sign = sgn(a1*b2 - a2*b1);// ���� ������������ ������ ���� �������� - �� ������ � ����� ���������
	
	x1 = x2; y1 = y2;
	x2 = x3; y2 = y3;
	
	for(i=4;i<=N;i++){
		scanf("%d %d", &x3, &y3);
		
		a1 = x2 - x1; a2 = y2 - y1; // ���������� ������� �������
		b1 = x3 - x2; b2 = y3 - y2;// ���������� ������� �������
		
		sign_t = sgn(a1*b2 - a2*b1);
		if(sign_t!=sign){
			printf("No");
			return 0;
		}
	}
	
	// ��������� �������� ��� ���������� � ������� �������
	
	a1 = x1_ - x3; a2 = y1_ - y3;
	b1 = x2_ - x1_; b2 = y2_ - y1_;
	
	sign_t = sgn(a1*b2 - a2*b1);
	if(sign_t!=sign){
		printf("No");
		return 0;
	}
	

	
	printf("Yes");
	return 0;
}

int sgn(int a){
	if(a>0) return 1;
	else return -1;
}
