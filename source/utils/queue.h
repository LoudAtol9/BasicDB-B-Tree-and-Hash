#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

struct queue
{
    void* info;
    struct queue* next;
};


void enqueue(struct queue** q, void* info);

void* dequeue(struct queue** q);

void free_queue(struct queue** q);


#endif