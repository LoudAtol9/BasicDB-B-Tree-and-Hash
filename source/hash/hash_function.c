#include "hash_function.h"

/*
 *  Caso precise deixar a string no formato
 * descrito na página 15 do pdf "Aula10-P1"
 *  Substitui o '\0' por ' ' e deixa num 
 * tamanho fixo descrito
 */
char* format_key(char* key)
{
    int i;
    int str_size;
    char* key_f = NULL;

    key_f = (char*) malloc(sizeof(char) * key_size);

    for (i = 0; key[i] != '\0' && key[i] != '|'; i++)
        key_f[i] = key[i];
    
    for (i = i; i < key_size; i++)
        key_f[i] = ' ';
    
    return key_f;
}


int my_calc_hash(char* key)
{
    int i;
    int pos;
    uint32_t sum = 0;

    if (key_size % 2 == 0)
    {
        for (i = 0; i < key_size; i = i + 2)
            sum = sum + key[i] * 100 + key[i+1];   
    }
    else
    {
        for (i = 0; i < key_size - 1; i = i + 2)
            sum = sum + key[i] * 100 + key[i+1];

        sum = sum + key[i] * 100;
    }

    return sum % table_size;
}


int calc_hash(char* key)
{
    uint32_t num;
    num = atoi(key);

    return num % table_size;
}