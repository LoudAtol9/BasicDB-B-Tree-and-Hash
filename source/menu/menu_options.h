#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include <stdio.h>
#include <stdbool.h>

#include "../database/file_utils.h"
#include "../database/busca.h"
#include "../database/insercao.h"
#include "../database/remocao.h"
#include "../database/compressao.h"
#include "../database/leitura.h"

#include "../menu/user_inputs.h"
#include "../menu/print_register.h"

#include "../b-trees/b-tree.h"
#include "../b-trees/busca_indice.h"
#include "../b-trees/insere_key.h"

#include "../hash/busca_hash.h"
#include "../hash/hash_io.h"
#include "../hash/insere_hash.h"
#include "../hash/remove_hash.h"

#include "../load-files/carrega_testes.h"

#include "../utils/string_utils.h"

/*
 * Oferece as opções:
 * - Criar Aquivo: chama "my_create"
 * - Carregar Arquivo: "chama my_fopen"
 * - Subrotina "naming files" chama "make_fdb_filename"
 * e make_index_filename para gerar o nome do arquivo e do indice
 */
void menu_file_options(FILE** fdb, int* tail, char** filename);

/*
 * Oferece as opções:
 * - Inserção:
 * - Remoção:
 * - Impressão:
 * - Compactação:
 * - Sair: chama "my_fclose" e termina o programa
 */
void menu_function_options(FILE* file, int* tail, char* filename);

#endif /*MENU_OPTIONS_H*/
