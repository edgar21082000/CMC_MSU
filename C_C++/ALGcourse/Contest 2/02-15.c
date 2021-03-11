#include <stdio.h>
#include <stdlib.h>

int main(void){
  unsigned int  n, i, *a, mask=0;
  scanf("%u",&n);
  a = (unsigned int *)malloc(n*sizeof(unsigned int));
  
  for (i=0; i<n; i++){
    scanf("%u", &a[i]);
    mask=mask^a[i];
  }
  
  unsigned int mask2=1;
  while ((mask&mask2)==0) mask2<<=1;
  
  unsigned int first=0;
  for (i=0; i<n; i++) if ((a[i]&mask2)!=0) first=first^a[i];
    
  unsigned int second=first^mask, sw;
  if (first<second)
  {
    sw=first;
    first=second;
    second=sw;
  }
  
  printf("%u %u", second, first);
  free(a);
  return 0;
}
