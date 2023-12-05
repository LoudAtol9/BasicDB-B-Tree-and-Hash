#ifndef BUSCA_INDICE_H
#define BUSCA_INDICE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "b-tree.h"

#include "../menu/print_register.h"

#include "../utils/queue.h"
#include "../utils/linked_list.h"

void read_reg_by_key(FILE* fp, FILE* bt_file, char* key, char** reg, int* size);
void print_all_reg(FILE* fp, FILE* bt_file);
int search_key(FILE* fp, char* key);

#endif