#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#define PATH_DB "../database/"

#include <stdio.h>
#include <stdlib.h>
#include "../database/remocao.h"
#include "../utils/string_utils.h"

/*
 * Gera o nome do arquivo .bin
 */
char* make_fdb_filename(char* filename);


/*
 * Cria o "database" pela primeira vez
 * Recebe as strings dos nomes
 * Retorna por ptr os file_ptr e o rabo lista ligada
 */
void my_create(FILE** fdb, int* tail, char* fdb_name);


/*
 * Abre um "database já existente"
 * Recebe as strings dos nomes
 * Retorna por ptr os file_ptr e o rabo lista ligada
 */
bool my_fopen(FILE** fdb, int* tail, char* fdb_name);


void push_file_offset(FILE* fp, int pos, int offset);

#endif /*FILE_UTILS_H*/