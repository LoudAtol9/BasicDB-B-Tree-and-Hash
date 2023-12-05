#include "carrega_testes.h"

char* read_test_file(FILE* fp, FILE* fp_pos, int* size)
{
    int i = 0;
    int j = 0;
    int zeroes = 0;
    int pos;

    char static_reg[134];
    char* din_reg = NULL;

    fseek(fp_pos, 0, SEEK_SET);
    fread(&pos, sizeof(int), 1, fp_pos);

    fseek(fp, pos, SEEK_SET);
    fread(static_reg, sizeof(char), 134, fp);

    fseek(fp_pos, 0, SEEK_SET);
    pos = ftell(fp);
    fwrite(&pos, sizeof(int), 1, fp_pos);

    for (i = 0; i < 134; i++)
    {
        if (static_reg[i] == '\0')
            zeroes++;
    }
    
    din_reg = (char*) malloc(sizeof(char) * (134 - (zeroes - 4)));

    for (i = 0; i < 3; i++)
        din_reg[j++] = static_reg[i]; 

    din_reg[j++] = '|';
    
    for (i = 4; i < 54 && static_reg[i] != '\0'; i++)
        din_reg[j++] = static_reg[i];   

    din_reg[j++] = '|';

    for (i = 54; i < 104 && static_reg[i] != '\0'; i++)
        din_reg[j++] = static_reg[i];
    
    din_reg[j++] = '|';

    for (i = 104; i < 134 && static_reg[i] != '\0'; i++)
        din_reg[j++] = static_reg[i];
    
    din_reg[j++] = '|';

    *size = j;
    return din_reg;
}