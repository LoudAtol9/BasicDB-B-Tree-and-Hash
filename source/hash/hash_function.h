#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <inttypes.h>

#include "hash_table.h"
#include "hash_io.h"


int calc_hash(char* key);
char* format_key(char* key);

#endif /*HASH_FUNC_H*/