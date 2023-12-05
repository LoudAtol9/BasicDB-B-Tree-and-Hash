#ifndef BUSCA_H
#define BUSCA_H

#include <stdio.h>
#include "../utils/linked_list.h"
#include "../utils/string_utils.h"

/*
 * Recebe uma posicao relativa do registro
 * Devolve a posicao do registro no arquivo
 * 
 * a posicao relativa nao conta os removidos
 */
int find_register(int pos, FILE* fp);

/*
 * Recebe um codigo de segurado
 * Devolve a posicao do registro no arquivo
 * 
 * Nao devolve removidos
 */
int find_register_per_code(FILE* fp, char* search_code);

#endif /*BUSCA_H*/