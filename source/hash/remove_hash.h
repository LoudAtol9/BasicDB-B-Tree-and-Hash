#ifndef REMOVE_HASH_H
#define REMOVE_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <inttypes.h>

#include "hash_table.h"
#include "hash_io.h"
#include "hash_function.h"

bool delete_key_in_hash(FILE* fp, char* key);

#endif /*REMOVE_HASH_H*/