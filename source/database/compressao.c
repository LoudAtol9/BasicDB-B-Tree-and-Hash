#include "compressao.h"

void delete_part_of_file(FILE* fp, int pos, int offset)
{
    int i = 0;
    int n = offset;
    char* buffer = NULL;

    /*Alloca o buffer na memoria*/
    buffer = (char*) malloc(sizeof(char) * offset);

    /*Pega pedacos do arquivo e sobrepoe*/
    for (i = 1; n == offset; i++)
    {
        /*Vai pro lugar que vai sobreescrever a pos*/
        fseek(fp, pos + (offset * i), SEEK_SET);
        /*enche o buffer*/
        n = fread(buffer, sizeof(char), offset, fp);
        /*Vai pra pos ser sobreescrita*/
        fseek(fp, pos + (offset * (i - 1)), SEEK_SET);
        /*despeja o buffer*/
        fwrite(buffer, offset, 1, fp);
    }
    /*repete ate acabar o arquivo*/

    free(buffer);
}

int my_defrager(FILE* fp, int* tail, char* filename)
{
    int rmv = 0;
    int read;
    int pos;
    int size;
    int off_set = 0;
    int old_file_size;
    int new_file_size = 0;
    char check;
    char sec_check = 'x';
    bool loop = true;

    fseek(fp, 0, SEEK_END);
    /*novo tamanho de arquivo*/
    old_file_size = ftell(fp);

    fseek(fp, sizeof(int), SEEK_SET);

    /*Percorre todo o arquivo cancando os elementos apagados*/
    /* e os espacos fragmentados*/
    do
    {
        read = fread(&check, sizeof(char), 1, fp);

        switch (check)
        {
        /*registro ocupado, só seguir*/
        case 'o':
            fread(&size, sizeof(int), 1, fp);
            fseek(fp, size, SEEK_CUR);
            break;
        /*area fragmentada, achar fim e sobreescrever*/
        case 'x':
            size = 0;
            pos = ftell(fp) - sizeof(char);
            sec_check = check;
            while (sec_check == 'x')
            {
                size++;
                fread(&sec_check, sizeof(char), 1, fp);
            }
            size++;
            delete_part_of_file(fp, pos, size);
            fseek(fp, pos, SEEK_SET);
            off_set = off_set + size;
            break;
        /*caso especifico de area fragmentada*/
        case 'X':
            pos = ftell(fp);
            delete_part_of_file(fp, pos, sizeof(char));
            fseek(fp, pos, SEEK_SET);
            off_set = off_set + sizeof(char);
            break;
        /*registro apagado, sobreescrever*/
        case '*':
            pos = ftell(fp) - sizeof(char);
            fread(&size, sizeof(int), 1, fp);
            delete_part_of_file(fp, pos, (size + sizeof(char) + sizeof(int)));
            fseek(fp, pos, SEEK_SET);
            off_set = off_set + (size + sizeof(char) + sizeof(int));
            break;
        }

    } while (read != 0 && (old_file_size - off_set > ftell(fp)));

    new_file_size = old_file_size - off_set;

    /*trunca o arquivo pro novo tamanho*/
    truncate(filename, new_file_size);
    fflush(fp);

    /*Atualiza o Header do arquivo*/
    /*reseta o header*/
    *tail = -1;

    fseek(fp, 0, SEEK_SET);
    fwrite(tail, sizeof(int), 1, fp);

    /*Reseta o tail*/
    *tail = 0;
    
    return 1;
}