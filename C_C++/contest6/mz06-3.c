#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char sh[] = "rwxrwxrwx";
enum
{
    SIZE = sizeof(sh) - 1,
};

int parse_rwx_permissions(const char *str);
 
int parse_rwx_permissions(const char *str)
{
    int ar = 0;

    if (str == NULL) {
        return -1;
    }    
    if (strlen(str) != SIZE) {
        return -1;
    }
    
    for (int i = 0; i < SIZE; i++) {
        if (str[i] == sh[i]) {
            ar += (1 << (SIZE - i - 1));
        } else if (str[i] != '-') {
            return -1;
        }
    }
    return ar;    
}

