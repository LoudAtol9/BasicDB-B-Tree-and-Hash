#include "busca_hash.h"

int search_key_in_hash(FILE* fp, char* key)
{
    int i;
    int hash_pos;
    int current_pos;

    char* key_f;
    struct hash_bucket* b;

    key_f = format_key(key);
    hash_pos = calc_hash(key_f);

    b = create_bucket();
    current_pos = hash_pos;

    do
    {
        /*Carrega o setor correspondente ao hash*/
        load_bucket(fp, b, current_pos);

        /*Percorre o setor em busca da chave*/
        for (i = 0; i < bucket_size; i++)
        {
            /*Achou, retorna a posição no database*/
            if (memcmp(&(b->keys[i * key_size]), key_f, key_size) == 0)
            {
                current_pos = b->db_pos[i];
                free_bucket(b);
                return current_pos;
            }
            /*Se encontrar um espaço vazio, a chave não existe no arquivo*/
            else if (b->keys[i * key_size] == EMPTY_SPACE)
            {
                free_bucket(b);
                printf("chave %s nao encontrada\n", key);
                return NIL;
            }     
        }

        /*Não está nesse setor vamos pro próximo*/
        /*"Overflow Progressivo"*/
        current_pos = (current_pos + 1) % table_size;
        
    } while (current_pos != hash_pos);
    /*Caso dê a volta no arquivo, a tabela está cheia e não tem a chave*/
    
    free_bucket(b);
    return NIL;
}


void read_reg_by_key_hash(FILE* fp, FILE* hash_file, char* key, char** reg, int* size)
{
    int file_pos;

    file_pos = search_key_in_hash(hash_file, key);

    fseek(fp, file_pos + sizeof(char), SEEK_SET);
    fread(size, sizeof(int), 1, fp);

    *reg = (char*) malloc(sizeof(char) * (*size));
    fread(*reg, sizeof(char), *size, fp);
}