#include "print_register.h"

void print_any_register(char* reg, int size)
{
    int i = 0;

    char* string_ptr = NULL;

    struct cel* ptr_list = NULL;
    struct cel* aux = NULL;

    add_elem(&ptr_list, reg);

    for (i = 0; i < size - 1; i++)
    {
        if (reg[i] == '|')
        {
            reg[i] = '\0';
            add_elem(&ptr_list, (reg + i + 1));
        }     
    }

    reg[i] = '\0';

    i = 0;

    for (aux = ptr_list; aux != NULL; aux = aux->next)
    {
        i++;
        string_ptr = (char*) aux->info;
        printf("Campo %d : %s\n", i, string_ptr);
    }

    free_list_only(ptr_list);
}