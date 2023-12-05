#include "leitura.h"

void read_reg_by_pos(FILE* fp, int pos, char** reg, int* size)
{
    int file_pos;

    file_pos = find_register(pos, fp);

    fseek(fp, file_pos + sizeof(char), SEEK_SET);

    fread(size, sizeof(int), 1, fp);

    *reg = (char*) malloc(sizeof(char) * (*size));

    fread(*reg, sizeof(char), *size, fp);
}

void read_reg_by_code(FILE* fp, char* code, char** reg, int* size)
{
    int file_pos;

    file_pos = find_register_per_code(fp, code);

    fseek(fp, file_pos + sizeof(char), SEEK_SET);

    fread(size, sizeof(int), 1, fp);

    *reg = (char*) malloc(sizeof(char) * (*size));

    fread(*reg, sizeof(char), *size, fp);
}


