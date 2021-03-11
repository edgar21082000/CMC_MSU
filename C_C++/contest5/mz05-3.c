void normalize_path(char *);

void normalize_path(char *buf)
{
    char *cpy;
    cpy = buf;
    int s_flag = 0;
    while(*cpy != '\0') {
        while(s_flag && *cpy == '/') {
            cpy++;
            if (*cpy == '\0') {
                break;
            }
        }
        *buf = *cpy;
        s_flag = 0;
        if (*cpy == '/') {
            s_flag = 1;
        }
        buf++;
        cpy++;
    }
    *buf = '\0';   
}


