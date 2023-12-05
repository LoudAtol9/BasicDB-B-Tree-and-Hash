#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct cel
{
    void* info;
    struct cel* next;
} CEL;

/*
 * Serve pra inserir um numero na lista ligada
 */
void add_elem(struct cel** head, void* info);

/*
 * Explode a lista sem vazar memória
 */
void free_list(struct cel* ptr);

/*
 * Explode a lista e nao libera a memoria dos ponteiros
 */
void free_list_only(struct cel* ptr);

/*
 * Remove elemento da lista com base na pos 
 */
bool remove_elem(struct cel** head, int index);

/*
 * Retorna o tamanho da lista
 */
int len_lista(struct cel* head);

/*
 * Retorna o ptr da cel que tiver esse num
 * Caso nao tenha na lista esse num ele retornara NULL
 */
struct cel* search_for_ptr(struct cel* head, void* ptr);

/*
 * Retorna o ptr da cel que tiver esse num
 * Caso nao tenha na lista esse num ele retornara NULL
 */
struct cel* search_for_pos(struct cel* head, int pos);


#endif /*LINKED_LIST_H*/