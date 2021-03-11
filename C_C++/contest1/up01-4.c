#include <ctype.h>

int mystrspccmp(const char *, const char *);

int
mystrspccmp(const char *str1, const char *str2)
{
    unsigned char *s1 = (unsigned char *) str1;
    unsigned char *s2 = (unsigned char *) str2;
    while (1) {
        while (isspace(*s1)) {
            s1++;
        }
        while (isspace(*s2)) {
            s2++;
        }
        if (*s1 - *s2 != 0 || !*s1) {
            break;
        }
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
