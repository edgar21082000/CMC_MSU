#include "my_library.h"
 
int main(void){
    size_t SIZE = 1<<10;
    char *str = (char *)malloc(SIZE*sizeof(char));
    if(!fgets(str, SIZE, stdin)) return 0;
    
    Tree *root = NULL;
    root = parser(root, str);
    if(!root) return 0;
    //tree_check(root); printf("\n\n\");
    
    Obj *res = calc(root);

    switch(res->type){
    case NUM:
        printf("%u\n", res->num);
        break;
    case TEXT:
        check_print(res->text);
        break;
    }
    
    return 0;
}
