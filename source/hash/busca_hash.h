#ifndef BUSCA_HASH_H
#define BUSCA_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <inttypes.h>

#include "hash_table.h"
#include "hash_io.h"
#include "hash_function.h"

int search_key_in_hash(FILE* fp, char* key);

void read_reg_by_key_hash(FILE* fp, FILE* hash_file, char* key, char** reg, int* size);

#endif /*BUSCA_HASH_H*/