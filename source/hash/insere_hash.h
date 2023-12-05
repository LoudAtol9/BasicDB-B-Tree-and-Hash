#ifndef INSERE_HASH_H
#define INSERE_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <inttypes.h>

#include "hash_table.h"
#include "hash_io.h"
#include "hash_function.h"

bool insert_key_in_hash(FILE* fp, char* key, int db_pos);


#endif /*INSERE_HASH_H*/