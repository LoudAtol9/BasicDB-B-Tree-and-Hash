#include "../database/busca.h"

int find_register(int pos, FILE* fp)
{
    int i = 0;
    int size = 0;
    int file_pos = sizeof(int);
    int read;
    char check = 'a';
    bool loop = true;

    /*Vai pro comeco dos registros do arq*/
    fseek(fp, sizeof(int), SEEK_SET);

    /*Enquanto nao chegar na pos*/
    do
    {
        loop = true;
        file_pos = ftell(fp);
        read = fread(&check, sizeof(char), 1, fp);

        while (loop)
        {
            switch (check)
            {
            case 'o':
                i++;
                fread(&size, sizeof(int), 1, fp);
                fseek(fp, size, SEEK_CUR);
                loop = false;
                break;
            case 'x':
                fread(&check, sizeof(char), 1, fp);
                break;
            case 'X':
                loop = false;
                break;
            case '*':
                fread(&size, sizeof(int), 1, fp);
                fseek(fp, size, SEEK_CUR);
                loop = false;
                break;
            }
        }

        if (read == 0)
            return -1;

    } while (i < pos);
    
    return file_pos;
}

int find_register_per_code(FILE* fp, char* search_code)
{
    int i = 0;
    int size = 0;
    int pos = 0;
    int read;
    char check;
    char code[4] = {'6', '6', '6', '\0'};
    bool loop = true;

    /*Vai pro comeco dos registros do arq*/
    fseek(fp, sizeof(int), SEEK_SET);

    /*Enquanto nao chegar na pos*/
    do
    {
        loop = true;
        pos = ftell(fp);
        read = fread(&check, sizeof(char), 1, fp);

        while (loop)
        {
            switch (check)
            {
            case 'o':
                i++;
                fread(&size, sizeof(int), 1, fp);
                fread(code, sizeof(char), 3, fp);
                fseek(fp, size - (3 * sizeof(char)), SEEK_CUR);
                code[3] = '\0';
                loop = false;
                break;
            case 'x':
                fread(&check, sizeof(char), 1, fp);
                break;
            case 'X':
                loop = false;
                break;
            case '*':
                fread(&size, sizeof(int), 1, fp);
                fseek(fp, size, SEEK_CUR);
                loop = false;
                break;
            }
        }

        if (read == 0)
            return -1;

    } while (!my_strcmp(code, search_code));
    
    return pos;
}