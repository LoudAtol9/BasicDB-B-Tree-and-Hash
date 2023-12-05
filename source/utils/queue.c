#include "queue.h"

void enqueue(struct queue** q, void* info)
{
    struct queue** aux = NULL;
    struct queue* new = NULL;

    for (aux = q; *aux != NULL; aux = &((*aux)->next));

    new = (struct queue*) malloc(sizeof(struct queue));
    new->info = info;
    new->next = NULL;

    *aux = new;
}

void* dequeue(struct queue** q)
{
    struct queue* del = NULL;
    void* ret = NULL;

    if (*q == NULL)
        return NULL;

    del = *q;
    ret = del->info;

    *q = (*q)->next;

    free(del);

    return ret;
}


void free_queue(struct queue** q)
{
    struct queue* del;
    struct queue* next;

    for (del = *q; del != NULL; del = next)
    {
        next = del->next;
        free(del);
    }
}

