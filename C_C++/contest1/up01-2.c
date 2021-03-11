#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int ch, len = 0, len_tmp = 0, flag = 0;
    while (!feof(stdin)) {
        ch = getchar();
        len_tmp++;
        if (ch < 'a' || ch > 'z') {
            if (len_tmp > len && flag != 1) {
                len = len_tmp - 1;
            }
            len_tmp = 0;
            flag = 0;
        }
        if (ch == 'q'){
            flag = 1;
        }
    }
    printf("%d\n", len);
    return 0;
}
