#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <unistd.h>
 
int
main(void)
{
    freopen("in.bin", "wb", stdout);
    char buf[] = "abababababababab";
    long long a[] = {5, 1, LLONG_MIN, 4};
    int k = 2;
    write(1, a, sizeof(a)); 
    write(1, &k, 4);
    return 0;
}

