#include "my_library.h"

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
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = TEXT;
    
    Obj *tmp = (Obj *)malloc(sizeof(Obj));
    tmp->type = TEXT;
    strcpy(tmp->text, num_to_str(left->type == NUM ? left->num : right->num));
    
    res = text_add((left->type == TEXT ? left : tmp), 
            (right->type == TEXT ? right : tmp));
    
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
    
    for(int i = 0; i < len_r; i++){
        for(int j = 0; j < len_l; j++){
            if(tmp[j] == '-')
                continue;
            
            if(right->text[i] == '?' || right->text[i] == tmp[j] || tmp[j] == '?'){
                tmp[j] = '-';
                break;
            }      
        }
    }
    
    int res_ind = 0;
    for(int i = 0; i < len_l; i++)
        if(tmp[i] != '-')
            res->text[res_ind++] = tmp[i];
    res->text[res_ind] = '\0';
    
    return res; 
}

Obj * mixed_sub(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = TEXT;
    
    Obj *tmp = (Obj *)malloc(sizeof(Obj));
    tmp->type = TEXT;
    strcpy(tmp->text, num_to_str(left->type == NUM ? left->num : right->num));
    
    res = text_sub((left->type == TEXT ? left : tmp), 
            (right->type == TEXT ? right : tmp));
            
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
    int lqcnt = 0, rqcnt = 0;
    for(int i = 0; i < len_l; i++)
        if(left->text[i] == '?')
            lqcnt++;
    for (int i = 0; i < len_r; i++)
        if(right->text[i] == '?')
            rqcnt++;
            
    if((lqcnt * len_r + len_l - lqcnt) >= (rqcnt * len_l + len_r - rqcnt))
        strcpy(res->text, make_res_text(left->text, right->text));
    else
        strcpy(res->text, make_res_text(right->text, left->text));
    
    return res;                 
}

Obj * mixed_mul(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = TEXT;
    
    Obj *tmp = (Obj *)malloc(sizeof(Obj));
    tmp->type = TEXT;
    strcpy(tmp->text, num_to_str(left->type == NUM ? left->num : right->num));
    
    res = text_mul((left->type == TEXT ? left : tmp), 
        (right->type == TEXT ? right : tmp));

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
    while((ptr = my_strstr(ptr, right->text))){
        for(int i = 0; i < len_r; i++){
            ptr[i] = '-';
        }
           
    }
    
    int index = 0;
    for(int i = 0; tmp[i] != '\0'; i++){
        if(tmp[i] == '-'){
            res->text[index++] = '?';
            i += len_r - 1;
        } else
            res->text[index++] = tmp[i];
    }

    return res;
}

Obj * mixed_divv(Obj *left, Obj *right){
    Obj *res = (Obj *)malloc(sizeof(Obj));
    res->type = TEXT;
    
    Obj *tmp = (Obj *)malloc(sizeof(Obj));
    tmp->type = TEXT;
    strcpy(tmp->text, num_to_str(left->type == NUM ? left->num : right->num));
    
    res = text_divv((left->type == TEXT ? left : tmp), 
        (right->type == TEXT ? right : tmp));
    
    return res;
}



//------------- helper functions -------------
char * num_to_str(unsigned cnt){
    char *tmp = (char *)malloc(1024);
    for(unsigned i = 0; i < cnt; i++)
        tmp[i] = '?';
    tmp[cnt] = '\0';
    return tmp;
}

char * make_res_text(char *l_text, char *r_text){
    char *res = (char *)malloc(1024); 
    int index = 0;
    int len_r = strlen(r_text);
    
    for(int i = 0; l_text[i] != '\0'; i++){
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
    
    for(int i = 0; str1[i] != '\0'; i++){
        int flag = 1;
        for(int j = 0; str2[j] != '\0'; j++){
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

