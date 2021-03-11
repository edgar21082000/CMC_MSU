#include <stdio.h>
#include <math.h>

unsigned int revers(unsigned int m);
void is_polindrom(unsigned int m);

int main(void){
	unsigned int m, n;
	scanf("%u%u", &m, &n);
	
	for(int i=0; i<n; i++) m += revers(m);
	is_polindrom(m); 
	
	return 0;
}

unsigned int revers(unsigned int m){
	unsigned int ans = 0, m_tmp = m, a = 0;
	while(m_tmp != 0){
		m_tmp/=10;
		a++;
	}
	
	for(int i=0; i<a; i++){
		ans += (m/(int)pow(10, a-1-i)) * (int)pow(10, i);
		m %= (int)pow(10, a-1-i); 
	}
	
	return ans;
}

void is_polindrom(unsigned int m){
	unsigned int a = 0, m_tmp = m, ans = m;
	
	while(m_tmp != 0){
		m_tmp/=10;
		a++;
	}
	
	for(int i=0; i<a/2; i++){
		if ( (int)(m/(int)pow(10, a-1-i)) != (int)((m%(int)pow(10, i+1))/pow(10, i)) ){
			printf("No");
			return;
		}
		m = m%(int)pow(10, a-1-i);
		m -= m%(int)pow(10, i+1);
	}
	
	printf("Yes\n%u", ans);
	return;
}
