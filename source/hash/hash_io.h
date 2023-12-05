#ifndef HASH_IO_H
#define HASH_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <inttypes.h>

#include "hash_table.h"

/*
 *  Cria o arquivo e seta as variáveis
 * da tabela hash de acordo com o passado
 */
FILE* create_hashtable(char* filename, int table_len, int key_len, int bucket_len);

/*
 *  Carrega o arquivo e seta as variáveis
 * da tabela hash
 */
FILE* load_hashtable(char* filename);

/*
 * Alloca na memória um bucket e escreve os valores padrões
 */
struct hash_bucket* create_bucket();

/*
 * Salva um bucket na posição do hash
 */
void save_bucket(FILE* fp, struct hash_bucket* b, int hash_pos);

/*
 * Carrega um bucket de uma posição do hash
 */
void load_bucket(FILE* fp, struct hash_bucket* b, int hash_pos);


#endif 