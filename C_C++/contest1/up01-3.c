#include <stdio.h>
#include <stdlib.h>

struct Pair
{
    int key;
    int value;
};

void process(struct Pair *, size_t);
int cmp(const void *, const void *);

void
process(struct Pair *data, size_t size)
{
    int *ind_arr = calloc(size, sizeof(*ind_arr));
    if (!ind_arr) {
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        ind_arr[i] = data[i].value;
        data[i].value = i;
    }
    qsort(data, size, sizeof(*data), cmp);
    for (int i = 0; i < size; i++) {
        data[i].value = ind_arr[data[i].value];
    }
    free(ind_arr);
}

int
cmp(const void *x, const void *y)
{
    if (((struct Pair *) x)->key < ((struct Pair *) y)->key) {
        return -1;
    } else if (((struct Pair *) x)->key > ((struct Pair *) y)->key) {
        return 1;
    } else {
        return ((struct Pair *) x)->value - ((struct Pair *) y)->value;
    }
}
