#include "remocao.h"

void remove_register(FILE* fp, int* tail, int pos)
{
    int size = 0;
    int file_pos = 0;
    int end = -1;
    char erase = '*';
    
    /*Aonde esta o arquivo a ser removido?*/
    file_pos = find_register(pos, fp);

    if (file_pos == -1)
    {
        printf("\nBusca fora do alcance...\n");
        return;
    }

    /*Muda o rabo da lista pra apontar pro novo rmv*/
    if (*tail == 0)
        fseek(fp, 0, SEEK_SET);
    else  
        fseek(fp, *tail + sizeof(char) + sizeof(int), SEEK_SET);
    fwrite(&file_pos, sizeof(int), 1, fp);

    /*Muda o estado do elemento*/
    fseek(fp, file_pos, SEEK_SET);
    fwrite(&erase, sizeof(char), 1, fp);
    fseek(fp, sizeof(int), SEEK_CUR);
    fwrite(&end, sizeof(int), 1, fp);

    /*Novo rabo da lista*/
    *tail = file_pos;

    fflush(fp);
}

void rmv_reg_by_code(FILE* fp, int* tail, char* search_code)
{
    int size = 0;
    int file_pos = 0;
    int end = -1;
    char erase = '*';
    
    /*Aonde esta o arquivo a ser removido?*/
    file_pos = find_register_per_code(fp, search_code);

    if (file_pos == -1)
    {
        printf("\nBusca fora do alcance...\n");
        return;
    }

    /*Muda o rabo da lista pra apontar pro novo rmv*/
    if (*tail == 0)
        fseek(fp, 0, SEEK_SET);
    else  
        fseek(fp, *tail + sizeof(char) + sizeof(int), SEEK_SET);
    fwrite(&file_pos, sizeof(int), 1, fp);

    /*Muda o estado do elemento*/
    fseek(fp, file_pos, SEEK_SET);
    fwrite(&erase, sizeof(char), 1, fp);
    fseek(fp, sizeof(int), SEEK_CUR);
    fwrite(&end, sizeof(int), 1, fp);

    /*Novo rabo da lista*/
    *tail = file_pos;

    fflush(fp);
}

int find_tail(FILE* fp)
{
    int pos = 0;
    int file_pos = 0;

    fseek(fp, pos, SEEK_SET);
    fread(&pos, sizeof(int), 1, fp);

    while (pos != -1)
    {
        fseek(fp, pos + sizeof(char) + sizeof(int), SEEK_SET);
        fread(&pos, sizeof(int), 1, fp);
        fseek(fp, -((sizeof(int) * 2) + sizeof(char)), SEEK_CUR);
        file_pos = ftell(fp);    
    }

    return file_pos;
}