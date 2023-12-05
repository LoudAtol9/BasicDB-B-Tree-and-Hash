#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <inttypes.h>

#define NIL -1
#define EMPTY_SPACE 127
#define REMOVED_SPACE 126

extern int table_size;
extern int key_size;
extern int bucket_size;

/*
 * keys eh uma matrix acessada por [i * tam + j]
 * db_pos é uma lista
 */
struct hash_bucket
{
    char* keys;
    int* db_pos;
};

/*
 * Alloca na memória um bucket e escreve os valores padrões
 */
struct hash_bucket* create_bucket();

void free_bucket(struct hash_bucket* b);

#endif /*HASH_TABLE_H*/