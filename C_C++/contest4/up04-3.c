#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
} Node;

void print(int, Node *);

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        exit(1);
    }
    Node root;
    int f = read(fd, &root, sizeof(root));
    if (f != sizeof(root)) {
        exit(1);
    }
    print(fd, &root);
    close(fd);
    return 0;
}

void
print(int fd, Node *cur)
{
    if (cur->right_idx == 0 && cur->left_idx == 0) {
        printf("%d\n", cur->key);
        return;
    }
    int next_r = cur->right_idx;
    int next_l = cur->left_idx;
    int cur_key = cur->key;
    int f;

    if (next_r) {
        lseek(fd, next_r * sizeof(*cur), SEEK_SET); // устанавливаем указатель файла на нужную структуру
        f = read(fd, cur, sizeof(*cur));
        if (f != sizeof(*cur)) {
            exit(1);
        }
        print(fd, cur);
    }

    printf("%d\n", cur_key);

    if (next_l) {
        lseek(fd, next_l * sizeof(*cur), SEEK_SET);
        f = read(fd, cur, sizeof(*cur));
        if (f != sizeof(*cur)) {
            exit(1);
        }
        print(fd, cur);
    }
}


