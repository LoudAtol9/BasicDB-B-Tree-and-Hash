#include "insere_hash.h"


bool insert_key_in_hash(FILE* fp, char* key, int db_pos)
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

        /*Percorre o setor em busca de um espaço livre*/
        for (i = 0; i < bucket_size; i++)
        {
            if (b->keys[i * key_size] == EMPTY_SPACE || b->keys[i * key_size] == REMOVED_SPACE)
            {
                /*Copia os dados pro setor*/
                memcpy(&(b->keys[i * key_size]), key_f, key_size);
                b->db_pos[i] = db_pos;

                /*Atualiza o setor no arquivo*/
                save_bucket(fp, b, current_pos);
                free_bucket(b);

                return true;
            }
            /* Caso não tivesse a checagem antes seria necessário
              este trecho de código...*/
            /*if (memcmp(&(b->keys[i * key_size]), key, key_size) == 0)
                return false;
            */
        }

        /*Setor ocupado vamos pro próximo*/
        /*"Overflow Progressivo"*/
        current_pos = (current_pos + 1) % table_size;
        
    } while (current_pos != hash_pos);
    /*Caso dê a volta no arquivo, a tabela está cheia e não pode ser inserido*/
    
    free_bucket(b);
    printf("\n Arquivo Hash está cheio, inserção não será possível\n");
    return false;
}