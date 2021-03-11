#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum{
    OPER, TEXT,  NUM, 
};

struct Object{
    int type;
    unsigned num;
    char text[1024];
    char op;
}typedef Obj;

struct Tree{
    struct Tree *parent;
    struct Tree *left;
    struct Tree *right;
    Obj *elem;
    int epl; // element_priority_level
}typedef Tree;


Tree * parser(Tree *, char *);
Tree * tree_add(Tree *, Tree *);
void check_print(char *);
void tree_check(Tree *);
void print_info(Tree *);


Obj * calc(Tree *);
Obj * add(Obj *, Obj *);
Obj * sub(Obj *, Obj *);
Obj * mul(Obj *, Obj *);
Obj * divv(Obj *, Obj *);

Obj * num_add(Obj *, Obj *);
Obj * text_add(Obj *, Obj *);
Obj * mixed_add(Obj *, Obj *);

Obj * num_sub(Obj *, Obj *);
Obj * text_sub(Obj *, Obj *);
Obj * mixed_sub(Obj *, Obj *);

Obj * num_mul(Obj *, Obj *);
Obj * text_mul(Obj *, Obj *);
Obj * mixed_mul(Obj *, Obj *);

Obj * num_divv(Obj *, Obj *);
Obj * text_divv(Obj *, Obj *);
Obj * mixed_divv(Obj *, Obj *);

char * num_to_str(unsigned);
char * make_res_text(char *, char *);
char * my_strstr(char *, char *);

