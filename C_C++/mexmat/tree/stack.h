#include "student.h"
#ifndef STACK_H
#define STACK_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STACK_INIT_SIZE 128

class Stack: publick student
{
    private:
        size_t size;
        size_t limit;
        student **data;
    public:
        Stack *createStack();
	void freeStack(Stack **s);
        void push(Stack *s, student *item);
        student *pop(Stack *s);
        student *peek(Stack *s);        
};

#endif
