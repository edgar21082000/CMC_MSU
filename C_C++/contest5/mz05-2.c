#include <stdio.h>

const char sh[] = "rwxrwxrwx";

enum
{
    IND = sizeof(sh) - 2 // убираем '\0' и + индексация
};

int main(int argc, char *argv[])
{
    int ar, cnt, sal;
    for(int i = 1; i < argc; i++) {
        sscanf(argv[i], "%o", &ar);
        sal = IND;
        char res;
        cnt = 1 << sal;
        while(cnt) {
            if (!(ar & cnt)) {
                res = '-';
            } else {
                res = sh[IND - sal];
            }
            printf("%c", res);
            sal--;
            cnt >>= 1;
        }
        printf("\n");
    }
    return 0;
}

