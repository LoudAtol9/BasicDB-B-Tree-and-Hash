#ifndef REMOCAO_H
#define REMOCAO_H

#include <stdio.h>
#include "../utils/linked_list.h"
#include "../utils/string_utils.h"
#include "../database/busca.h"

void remove_register(FILE* fp, int* tail, int pos);

void rmv_reg_by_code(FILE* fp, int* tail, char* search_code);

/*
 * Acha a posicao do final das listas dos removidos
 */
int find_tail(FILE* fp);

#endif /*REMOCAO_H*/