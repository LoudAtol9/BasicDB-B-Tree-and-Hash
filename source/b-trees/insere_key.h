#ifndef INSERE_KEY_H
#define INSERE_KEY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../utils/stack.h"

#include "b-tree.h"


void insert_btree(FILE* fp, char* key, int db_pos);
 
#endif