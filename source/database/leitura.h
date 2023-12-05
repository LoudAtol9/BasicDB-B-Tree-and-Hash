#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>
#include "../utils/linked_list.h"
#include "../utils/string_utils.h"
#include "../database/busca.h"

void read_reg_by_pos(FILE* fp, int pos, char** reg, int* size);

void read_reg_by_code(FILE* fp, char* code, char** reg, int* size);

#endif /*REMOCAO_H*/