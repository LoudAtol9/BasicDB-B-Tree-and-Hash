#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

struct stack
{
    void* info;
    struct stack* next;
};

void push(struct stack** s, void* info);

void* pop(struct stack** s);

void free_stack(struct stack* s);

#endif /*STACK_h*/