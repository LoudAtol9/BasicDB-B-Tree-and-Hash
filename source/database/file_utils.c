#include "file_utils.h"


char* make_fdb_filename(char* filename)
{
    int i = 0;
    int j = 0;
    int str_len = 0;
    char* path = "../source/files/";
    char* type = ".bin";
    char* fdb_name;

    str_len = my_strlen(filename);
    fdb_name = malloc((sizeof(char) * (5 + 16)) + str_len);

    for (j = 0; j < 16; j++)
    {
        fdb_name[i] = path[j];
        i++;
    }
    for (j = 0; j < str_len; j++)
    {
        fdb_name[i] = filename[j];
        i++;
    }
    for (j = 0; j < 5; j++)
    {
        fdb_name[i] = type[j];
        i++;
    }      
    
    printf("%s", fdb_name);

    return fdb_name;
}


void my_create(FILE** fdb, int* tail, char* fdb_name)
{
    int end = -1;

    *fdb = fopen(fdb_name, "w+");
    fwrite(&end, sizeof(int), 1, *fdb);
    fclose(*fdb);

    *fdb = fopen(fdb_name, "r+");
    *tail = find_tail(*fdb);

    fflush(*fdb);
}


bool my_fopen(FILE** fdb, int* tail, char* fdb_name)
{
    *fdb = fopen(fdb_name, "r+");
    if (*fdb == NULL)
    {
        printf("\nNao existe arquivo com este nome.\n");
        return false;
    }

    *tail = find_tail(*fdb); 
    
    return true;
}


// Testar alem, nao tenho ctz que isso funciona
void push_file_offset(FILE* fp, int pos, int offset)
{
    int i;
    int size;
    char* buffer;

    buffer = (char*) malloc(offset);

    fseek(fp, 0, SEEK_END);

    for (i = 0; ftell(fp) >= pos; i = i + offset)
    {
        offset = (ftell(fp) - pos) % (offset + 1);
        fseek(fp, -offset, SEEK_CUR);
        fread(buffer, offset, 1, fp);
        fwrite(buffer, offset, 1, fp);
        if ((ftell(fp) - (3 * offset)) < 0)
            fseek(fp, (-2 * offset) - 1, SEEK_CUR);
        else
            fseek(fp, (-3 * offset), SEEK_CUR);
    }

    free(buffer);
}



