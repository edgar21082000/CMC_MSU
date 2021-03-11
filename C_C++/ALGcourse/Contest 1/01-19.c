#include <stdio.h>
#include <math.h>

int main(void){
	unsigned int a11, a12, a21, a22, b1, b2;
	scanf("%u%u", &a11, &a12);
	scanf("%u%u", &a21, &a22);
	scanf("%u%u", &b1, &b2);
	
	unsigned int t11, t12, t21, t22, s1, s2;	

	unsigned int mask = 1;
	unsigned int x = 0, y = 0;
	unsigned int bit_x, bit_y;
	
	
	int i;
	for(i=0;i<32;i++){
		t11 = a11&mask;
		t12 = a12&mask;
		t21 = a21&mask;
		t22 = a22&mask;
		s1 = b1&mask;
		s2 = b2&mask;
		
		//printf("%u %u %u %u %u %u \n", t11, t12, t21, t22, s1, s2);
		
		// для х, у имеем варианты 0 0, 0 1, 1 0, 1 1;
		
		bit_x = 0; bit_y = 0; 
		
		
		
		
		//printf("bit_xy___%u %u\n", bit_x, bit_y);
		//printf("%u = %u\n%u %u\n", (t11&bit_x)^(t12&bit_y), s1, (t21&bit_x)^(t22&bit_y), s2  );
		
		if( ( ((t11&bit_x)^(t12&bit_y)) == s1) && ( ((t21&bit_x)^(t22&bit_y)) == s2) ){
			mask<<=1; // проверяем следующий бит
			continue;
		}
		
		bit_x = 0; bit_y = pow(2, i); 
		
		//printf("bit_xy___%u %u\n", bit_x, bit_y);
		//printf("%u = %u\n%u %u\n", (t11&bit_x)^(t12&bit_y), s1, (t21&bit_x)^(t22&bit_y), s2  );
		
		if( ( ((t11&bit_x)^(t12&bit_y)) == s1) && ( ((t21&bit_x)^(t22&bit_y)) == s2) ){
			y += bit_y;
			mask<<=1; // проверяем следующий бит
			continue;
		}
		
		bit_x = pow(2, i); bit_y = 0; 
		
		//printf("bit_xy___%u %u\n", bit_x, bit_y);
		//printf("%u = %u\n%u %u\n", (t11&bit_x)^(t12&bit_y), s1, (t21&bit_x)^(t22&bit_y), s2  );
		
		if( ( ((t11&bit_x)^(t12&bit_y)) == s1) && ( ((t21&bit_x)^(t22&bit_y)) == s2) ){
			x += bit_x;
			mask<<=1; // проверяем следующий бит
			continue;
		}
		
		bit_x = pow(2, i); bit_y = pow(2, i); 
		
		//printf("bit_xy___%u %u\n", bit_x, bit_y);
		//printf("%u = %u\n%u %u\n", (t11&bit_x)^(t12&bit_y), s1, (t21&bit_x)^(t22&bit_y), s2  );
		
		if( ( ((t11&bit_x)^(t12&bit_y)) == s1) && ( ((t21&bit_x)^(t22&bit_y)) == s2) ){
			x += bit_x;
			y += bit_y;
			mask<<=1; // проверяем следующий бит
			continue;
		}
		
		
		// доходит до этой строчки если ни одно из условий не выполняется => не возможно подобрать такие биты => и числа х у тожу 
		
		printf("No\n");
		return 0;
	}
	
	printf("Yes\n%u %u", x, y);
	
	return 0;
}
