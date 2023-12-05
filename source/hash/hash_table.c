#include "hash_table.h"

int table_size;
int key_size;
int bucket_size;

/*
 * Alloca na memória um bucket e escreve os valores padrões
 */
struct hash_bucket* create_bucket()
{
    int i;
    int nil = NIL;
    char emp_spc = EMPTY_SPACE;

    struct hash_bucket* b;

    b = (struct hash_bucket*) malloc(sizeof(struct hash_bucket));

    b->db_pos = (int*) malloc(sizeof(int) * bucket_size);
    b->keys = (char*) malloc(sizeof(char) * bucket_size * key_size);

    for (i = 0; i < bucket_size * key_size; i++)
        b->keys[i] = EMPTY_SPACE;
    for (i = 0; i < bucket_size; i++)
        b->db_pos[i] = NIL;

    return b;
}


/*
 * Libera o espaço de memória ocupado pelo bucket
 */
void free_bucket(struct hash_bucket* b)
{
    free(b->db_pos);
    free(b->keys);
    free(b);
}