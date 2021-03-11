#include "my_library.h"

Tree * parser(Tree *root, char *str){
    int open_brackets_cnt = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(isspace(str[i]))
            continue;    
            
        if(isdigit(str[i])){
            unsigned tmp = str[i] - '0';
            while(isdigit(str[++i])){ // закончится на неиследанном
                tmp *= 10;
                tmp += str[i] - '0';
            }
            
            Obj *elem = (Obj *)malloc(sizeof(Obj));
            elem->type = NUM;
            elem->num = tmp;
            
            Tree *new = (Tree *)malloc(sizeof(Tree));
            new->epl = 0;
            new->elem = elem;
            new->epl += 3 + 10*open_brackets_cnt;
            
            root = tree_add(root, new); 
            
            i--;
            continue;
        }
        
        if(str[i] == '"'){
            Obj *elem = (Obj *)malloc(sizeof(Obj));
            elem->type = TEXT;
            
            int j = 0;
            while(str[++i] != '"'){
                elem->text[j++] = str[i];
            }
            elem->text[j] = '\0';
            
            Tree *new = (Tree *)malloc(sizeof(Tree));
            new->epl = 0;
            new->elem = elem;
            new->epl += 3 + 10*open_brackets_cnt;
            
            root = tree_add(root, new); 
            
            continue;
        }
        
        if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'){
            Obj *elem = (Obj *)malloc(sizeof(Obj));
            elem->type = OPER;
            elem->op = str[i];
            
            Tree *new = (Tree *)malloc(sizeof(Tree));
            new->epl = 0;
            new->elem = elem;
            new->epl += ((str[i] == '+' || str[i] == '-') ? 1 : 2) + 10*open_brackets_cnt;
            
            root = tree_add(root, new); 
                        
            continue;   
        }
        
        if(str[i] == '(' || str[i] == ')'){
            if(str[i] == '(')
                open_brackets_cnt++;
            else
                open_brackets_cnt--;
            continue;
        }
    }
    return root;
}

Tree * tree_add(Tree *root, Tree *new){
    if (root == NULL){
        root = (Tree *)malloc(sizeof(Tree));
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        root->elem = new->elem;
        root->epl = new->epl;
    } else if(new->epl <= root->epl){
        
        if(root->parent == NULL){
            root->parent = (Tree *)malloc(sizeof(Tree));
            root->parent->parent = NULL;
            root->parent->left = root;
            root->parent->right = NULL;
            root->parent->elem = new->elem;
            root->parent->epl = new->epl;
            return root->parent;
        } else {
            Tree *ins_vertex = (Tree *)malloc(sizeof(Tree));
            ins_vertex->elem = new->elem;
            ins_vertex->epl = new->epl;
            ins_vertex->parent = root->parent;
            ins_vertex->left = root;
            ins_vertex->right = NULL;
            
            root->parent->right = ins_vertex;
            root->parent = ins_vertex; 
            return ins_vertex;
        }
    } else {
        root->right = tree_add(root->right, new);
        root->right->parent = root;
        
    }
    return root;
}

void check_print(char *str){
    int len = strlen(str);
    
    for(int i = 0; i < len; i++){
        if (str[i] != '?'){
            printf("%s\n", str);
            return;
        }
    }
    printf("%d\n", len);
}

//------------------------------------------------------------------------------------

void tree_check(Tree *root){
    if(root != NULL){
        tree_check(root->left);
        print_info(root);
        tree_check(root->right);
    }
}

void print_info(Tree *root){
    printf("-----------------------------\n");
    if(root->parent != NULL) printf("Has parent\n");
    if(root->left != NULL) printf("Has left\n");
    if(root->right != NULL) printf("Has right\n");
    switch(root->elem->type){
    case OPER:
        printf("OPER: %c\n", root->elem->op);
        break;
    case NUM:
        printf("NUM: %u\n", root->elem->num);
        break;
    case TEXT:
        printf("TEXT: %s\n", root->elem->text);
        break;
    }   
    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n");
}

