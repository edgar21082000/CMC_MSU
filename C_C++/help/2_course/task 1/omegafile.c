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
void * free_tree(Tree *);
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
    
    free_tree(root); 
    free(str); 
    
    return 0;
}



Tree * parser(Tree *root, char *str){
    int open_brackets_cnt = 0;
    int i = 0;
    for(i = 0; str[i] != '\0'; i++){
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
            free(new);
            
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
            free(new);
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
            free(new);           
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

void * free_tree(Tree *root){
    if(root != NULL){
        free_tree(root->left);
        free_tree(root->right);
        free(root->elem);
        free(root);
    }
}

void check_print(char *str){
    int len = strlen(str);
    int i = 0;
    for(i = 0; i < len; i++){
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



Obj * calc(Tree *root){
    if(root->elem->type == OPER){
    
        switch(root->elem->op){
        case '+':
            free(root->elem);
            return (root->elem = add(calc(root->left), calc(root->right)));
            break;
        case '-':
            free(root->elem);
            return (root->elem = sub(calc(root->left), calc(root->right)));
            break;
        case '*':
            free(root->elem);
            return (root->elem = mul(calc(root->left), calc(root->right)));
            break;
        case '/':
            free(root->elem);
            return (root->elem = divv(calc(root->left), calc(root->right)));
            break;
        }
    }
    return root->elem;
}


Obj * add(Obj *left, Obj *right){
    if(left->type == NUM && right->type == NUM)
        return num_add(left, right);
    else if(left->type == TEXT && right->type == TEXT)
        return text_add(left, right);
    else if(left->type != right->type)
        return mixed_add(left, right);
    return NULL;
}

Obj * sub(Obj *left, Obj *right){
    if(left->type == NUM && right->type == NUM)
        return num_sub(left, right);
    else if(left->type == TEXT && right->type == TEXT)
        return text_sub(left, right);
    else if(left->type != right->type)
        return mixed_sub(left, right);
    return NULL;
}

Obj * mul(Obj *left, Obj *right){
    if(left->type == NUM && right->type == NUM)
        return num_mul(left, right);
    else if(left->type == TEXT && right->type == TEXT)
        return text_mul(left, right);
    else if(left->type != right->type)
        return mixed_mul(left, right);
    return NULL;
}

Obj * divv(Obj *left, Obj *right){
    if(left->type == NUM && right->type == NUM)
        return num_divv(left, right);
    else if(left->type == TEXT && right->type == TEXT)
        return text_divv(left, right);
    else if(left->type != right->type)
        return mixed_divv(left, right);
    return NULL;
}

char *plus;
//-----------------   '+'   -----------------
Obj * num_add(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = NUM;
    res->num = left->num + right->num;
    return res;
}

Obj * text_add(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = TEXT;
    strcpy(res->text, left->text);
    strcat(res->text, right->text);
    return res;
}

Obj * mixed_add(Obj *left, Obj *right){
    Obj *res;
    
    Obj *tmp = (Obj *)malloc(sizeof(Obj));
    tmp->type = TEXT;
    strcpy(tmp->text, plus = num_to_str(left->type == NUM ? left->num : right->num));
    free(plus);
    res = text_add((left->type == TEXT ? left : tmp), 
            (right->type == TEXT ? right : tmp));
    free(tmp);
    return res;    
}

//-----------------   '-'   -----------------
Obj * num_sub(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = NUM;
    res->num = left->num > right->num ? left->num - right->num : 0;
    return res;
}

Obj * text_sub(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = TEXT;
    
    int len_r = strlen(right->text); 
    int len_l = strlen(left->text);
    char tmp[1024];
    strcpy(tmp, left->text);
    
    int i = 0, j = 0;
    for(i = 0; i < len_r; i++){
        for(j = 0; j < len_l; j++){
            if(tmp[j] == '-')
                continue;
            
            if(right->text[i] == '?' || right->text[i] == tmp[j] || tmp[j] == '?'){
                tmp[j] = '-';
                break;
            }      
        }
    }
    
    int res_ind = 0;
    for(i = 0; i < len_l; i++)
        if(tmp[i] != '-')
            res->text[res_ind++] = tmp[i];
    res->text[res_ind] = '\0';
    
    return res; 
}

Obj * mixed_sub(Obj *left, Obj *right){
    Obj *res;
    
    Obj *tmp = (Obj *)malloc(sizeof(Obj));
    tmp->type = TEXT;
    strcpy(tmp->text, plus = num_to_str(left->type == NUM ? left->num : right->num));
    free(plus);
    res = text_sub((left->type == TEXT ? left : tmp), 
            (right->type == TEXT ? right : tmp));
    free(tmp);        
    return res;
}

//-----------------   '*'   -----------------
Obj * num_mul(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = NUM;
    res->num = left->num * right->num;
    return res;
}

Obj * text_mul(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = TEXT;
    
    int len_l = strlen(left->text); 
    int len_r = strlen(right->text);
    int lqcnt = 0, rqcnt = 0, i = 0;
    for(i = 0; i < len_l; i++)
        if(left->text[i] == '?')
            lqcnt++;
    for (i = 0; i < len_r; i++)
        if(right->text[i] == '?')
            rqcnt++;
            
    if((lqcnt * len_r + len_l - lqcnt) >= (rqcnt * len_l + len_r - rqcnt))
        strcpy(res->text, plus = make_res_text(left->text, right->text));
    else
        strcpy(res->text, plus = make_res_text(right->text, left->text));
    free(plus);
    return res;                 
}

Obj * mixed_mul(Obj *left, Obj *right){
    Obj *res;
    
    Obj *tmp = (Obj *)malloc(sizeof(Obj));
    tmp->type = TEXT;
    strcpy(tmp->text, plus = num_to_str(left->type == NUM ? left->num : right->num));
    free(plus);
    res = text_mul((left->type == TEXT ? left : tmp), 
        (right->type == TEXT ? right : tmp));
    free(tmp);
    return res;
}

//-----------------   '/'   -----------------
Obj * num_divv(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = NUM;
    res->num = left->num / right->num + left->num % right->num; 
    return res;
}

Obj * text_divv(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = TEXT;
    
    char tmp[1024];
    strcpy(tmp, left->text);
    char *ptr = tmp;
    
    int len_r = strlen(right->text);
    int i = 0;
    while((ptr = my_strstr(ptr, right->text))){
        for(i = 0; i < len_r; i++){
            ptr[i] = '-';
        }
           
    }
    
    int index = 0;
    for(i = 0; tmp[i] != '\0'; i++){
        if(tmp[i] == '-'){
            res->text[index++] = '?';
            i += len_r - 1;
        } else
            res->text[index++] = tmp[i];
    }

    return res;
}

Obj * mixed_divv(Obj *left, Obj *right){
    Obj *res;
    
    Obj *tmp = (Obj *)malloc(sizeof(Obj));
    tmp->type = TEXT;
    strcpy(tmp->text, plus = num_to_str(left->type == NUM ? left->num : right->num));
    free(plus);
    res = text_divv((left->type == TEXT ? left : tmp), 
        (right->type == TEXT ? right : tmp));
    free(tmp);
    return res;
}



//------------- helper functions -------------
char * num_to_str(unsigned cnt){
    char *tmp = (char *)malloc(1024);
    unsigned i = 0;
    for(i = 0; i < cnt; i++)
        tmp[i] = '?';
    tmp[cnt] = '\0';
    return tmp;
}

char * make_res_text(char *l_text, char *r_text){
    char *res = (char *)malloc(1024); 
    int index = 0;
    int len_r = strlen(r_text);
    int i = 0;
    for(i = 0; l_text[i] != '\0'; i++){
        if(l_text[i] != '?')
            res[index++] = l_text[i];
        else{
            strcat(res + index, r_text);
            index += len_r;
        }    
    }
    return res;
}

char * my_strstr(char *str1, char *str2){
    if (strlen(str2) > strlen(str1)) return NULL;
    
    int i = 0, j = 0;
    for(i = 0; str1[i] != '\0'; i++){
        int flag = 1;
        for(j = 0; str2[j] != '\0'; j++){
            if(str1[i+j] == '-' || str1[i+j] == '\0'){
                flag = 0;
                break;
            }
            if(str1[i+j] != str2[j] && str1[i+j] != '?' && str2[j] != '?'){
                flag = 0;
                break;    
            }
        }
        if(flag) return (str1 + i);      
    }    
    return NULL;
}

