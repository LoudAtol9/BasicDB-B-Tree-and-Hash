#include "hash_io.h"


FILE* create_hashtable(char* filename, int table_len, int key_len, int bucket_len)
{
    int i;
    int j;
    int nil = NIL;
    char emp_spc = EMPTY_SPACE; 
    FILE* fp;

    fp = fopen(filename, "w+");
    fclose(fp);
    fp = fopen(filename, "r+");

    table_size = table_len;
    key_size = key_len;
    bucket_size = bucket_len;

    fwrite(&table_size, sizeof(int), 1, fp);
    fwrite(&key_size, sizeof(int), 1, fp);
    fwrite(&bucket_size, sizeof(int), 1, fp);

    for (i = 0; i < table_len; i++)
    {
        for (j = 0; j < bucket_size * key_size; j++)
            fwrite(&emp_spc, sizeof(char), 1, fp);
        for (j = 0; j < bucket_size; j++)
            fwrite(&nil, sizeof(int), 1, fp);
    }

    return fp;
}

FILE* load_hashtable(char* filename)
{
    FILE* fp;

    fp = fopen(filename, "r+");

    if (fp != NULL)
    {
        fread(&table_size, sizeof(int), 1, fp);
        fread(&key_size, sizeof(int), 1, fp);
        fread(&bucket_size, sizeof(int), 1, fp);
    }
    return fp;
}


/*
 * É um FSEEK pro arquivo de Hash
 * Traduz a posição que seria um indice do hash
 * 0, 1 , 2 , 3, 4 , 5
 * para as correspondentes no arq
 * 8, 78, 148, 218, 288,  
 * Função Inline, não tem custo de stack
 */
void fseek_for_hash(FILE* fp, int hash_pos)
{
    //        posição     x      tamanho do bucket atual          +      header
    fseek(fp, hash_pos * (bucket_size * (key_size + sizeof(int))) + (3 * sizeof(int)), SEEK_SET);
}


/*
 * Salva um bucket na posição do hash
 */
void save_bucket(FILE* fp, struct hash_bucket* b, int hash_pos)
{
    fseek_for_hash(fp, hash_pos);

    fwrite(b->keys, sizeof(char), bucket_size * key_size, fp);
    fwrite(b->db_pos, sizeof(int), bucket_size, fp);
}

/*
 * Carrega um bucket de uma posição do hash
 */
void load_bucket(FILE* fp, struct hash_bucket* b, int hash_pos)
{
    fseek_for_hash(fp, hash_pos);

    fread(b->keys, sizeof(char), bucket_size * key_size, fp);
    fread(b->db_pos, sizeof(int), bucket_size, fp);
}