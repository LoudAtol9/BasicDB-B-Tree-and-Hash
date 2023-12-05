#include "stack.h"

void push(struct stack** s, void* info)
{
    struct stack* new = NULL;

    new = (struct stack*) malloc(sizeof(struct stack));
    new->info = info;
    new->next = *s;

    *s = new;
}

void* pop(struct stack** s)
{
    struct stack* del;
    void* ret;

    if (*s == NULL)
        return NULL;
    
    del = *s;
    ret = del->info;
    *s = (*s)->next;

    free(del);

    return ret;
}

void free_stack(struct stack* s)
{
    if (s != NULL)
    {
        free_stack(s->next);
        free(s->info);
        free(s);
    }
}
