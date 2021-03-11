#include <iostream>
#include "stack.h"

Stack* Stack::createStack() {
    Stack *tmp = (Stack*) malloc(sizeof(Stack));
    tmp->limit = STACK_INIT_SIZE;
    tmp->size = 0;
    tmp->data = (student **)malloc(tmp->limit * sizeof(student *));
    return tmp;
}
 
void Stack::freeStack(Stack **s) {
    free((*s)->data);
    free(*s);
    *s = NULL;
}
 
void Stack::push(Stack *s, student *item) {
    if (s->size >= s->limit) {
        s->limit <<= 1;
        s->data = (student **)realloc(s->data, s->limit * sizeof(student *));
    }
    s->data[s->size++] = item;
}
 
student* Stack::pop(Stack *s) {
    if (s->size == 0) {
        exit(1);
    }
    s->size--;
    return s->data[s->size];
}
 
student* Stack::peek(Stack *s) {
    return s->data[s->size-1];
}
