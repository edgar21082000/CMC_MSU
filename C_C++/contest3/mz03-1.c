
int bitcount(STYPE);

int bitcount(STYPE value)
{
    int count = 0;
    UTYPE tmp = (UTYPE) value;
    do {
        if (tmp & 1) {
            count++;
        }
    } while (tmp >>= 1);
    return count; 
}
