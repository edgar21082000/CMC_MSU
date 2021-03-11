#include "my_library.h"

Obj * calc(Tree *root){
    if(root->elem->type == OPER){
    
        switch(root->elem->op){
        case '+':
            return add(calc(root->left), calc(root->right));
            break;
        case '-':
            return sub(calc(root->left), calc(root->right));
            break;
        case '*':
            return mul(calc(root->left), calc(root->right));
            break;
        case '/':
            return divv(calc(root->left), calc(root->right));
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

