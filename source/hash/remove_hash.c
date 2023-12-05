#include "remove_hash.h"

bool delete_key_in_hash(FILE* fp, char* key)
{
    int i;
    int j;
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
            /*Achou, vamos apaga-la*/
            if (memcmp(&(b->keys[i * key_size]), key_f, key_size) == 0)
            {
                /*Apagando...*/
                for (j = 0; j < key_size; j++)
                    b->keys[(i * key_size) + j] = REMOVED_SPACE;
                b->db_pos[i] = NIL;

                /*Salvando alterações*/
                save_bucket(fp, b, current_pos);

                free_bucket(b);
                return true;
            }
            /*Se encontrar um espaço vazio, a chave não existe no arquivo*/
            else if (b->keys[i * key_size] == EMPTY_SPACE)
            {
                free_bucket(b);
                return false;
            }    
            
        }

        /*Não está nesse setor vamos pro próximo*/
        /*"Overflow Progressivo"*/
        current_pos = (current_pos + 1) % table_size;
        
    } while (current_pos != hash_pos);
    /*Caso dê a volta no arquivo, a tabela está cheia e não tem a chave*/
    
    free_bucket(b);
    return false;
}