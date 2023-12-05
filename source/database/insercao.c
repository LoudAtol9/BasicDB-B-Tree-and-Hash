#include "../database/insercao.h"

/*
 *  Retorna a posicao que sera inserido o registro
 * caso retorne -1, eh pra ser inserido no final do arquivo
 */
int best_fit(FILE* fp, int size)
{
    int i;
    int diff = 0;
    int min_diff = INT_MAX;
    int pos;
    int old_pos = 0;
    int min_old_pos;
    int next_pos;
    int min_pos = -1;
    int reg_size;

    char erase = '*';
    char frag = 'x';
    char stop_frag = 'X';

    fseek(fp, 0, SEEK_SET);

    fread(&pos, sizeof(int), 1, fp);
    
    /*enquanto nao chegar ao fim da lista*/
    while (pos != -1)
    {
        fseek(fp, pos + sizeof(char), SEEK_SET);

        fread(&reg_size, sizeof(int), 1, fp);

        diff = reg_size - size;

        if (reg_size >= size && diff < min_diff)
        {
            min_diff = diff;
            min_pos = pos;
            min_old_pos = old_pos;
        }

        old_pos = pos;
        fread(&pos, sizeof(int), 1, fp);
    }

    /*Nao encaixou em nenhum lugar, vai pro final do arq*/
    if (min_pos == -1)
        return -1;

    /*Vai pro espaco que "sobrou"*/
    fseek(fp, min_pos + sizeof(char), SEEK_SET);
    fread(&reg_size, sizeof(int), 1, fp);
    fread(&next_pos, sizeof(int), 1, fp);
    fseek(fp, size - (sizeof(int)), SEEK_CUR);

    pos = ftell(fp);
    
    /*Nao cabe um indice*/
    if (min_diff == 0)
    {
        if (min_old_pos == 0)
            fseek(fp, 0, SEEK_SET);
        else
            fseek(fp, min_old_pos + sizeof(char)+ sizeof(int), SEEK_SET);
        fwrite(&next_pos, sizeof(int), 1, fp);
    }
    else if (min_diff < (2 * sizeof(int)) + sizeof(char))
    {
        /*Enche de 'x' o local*/
        for (i = 0; i < min_diff - 1; i++)
            fwrite(&frag, sizeof(char), 1, fp);
        fwrite(&stop_frag, sizeof(char), 1, fp);
        /*Volta e atualiza endereco anterior para o proximo*/
        if (min_old_pos == 0)
            fseek(fp, 0, SEEK_SET);
        else
            fseek(fp, min_old_pos + sizeof(char)+ sizeof(int), SEEK_SET);
        fwrite(&next_pos, sizeof(int), 1, fp);
    }
    /*Cabe um indice*/
    else
    {
        /*Escreve o indice com as informacoes atualizadas*/
        min_diff = min_diff - (sizeof(int) + sizeof(char));
        fwrite(&erase, sizeof(char), 1, fp);
        fwrite(&min_diff, sizeof(int), 1, fp);
        fwrite(&next_pos, sizeof(int), 1, fp);
        /*Volta e atualiza endereco anterior*/
        if (min_old_pos == 0)
            fseek(fp, 0, SEEK_SET);
        else
            fseek(fp, min_old_pos + sizeof(char) + sizeof(int), SEEK_SET);
        fwrite(&pos, sizeof(int), 1, fp);
    }

    return min_pos;    
}



int insert_in_file(FILE* fp, char* reg, size_t size)
{
    int pos = 0;
    char content = 'o';

    /*Recebe a posicao pra inserir no arquivo*/
    pos = best_fit(fp, size);

    /*Caso seja -1 vai pro final do arq*/
    if (pos == -1)
    {
        fseek(fp, 0, SEEK_END);
        pos = ftell(fp);
    }
    /*Senao vai pra posicao*/
    else
    {
        /*Vai pra posicao*/
        fseek(fp, pos, SEEK_SET);
    }
        
    /*Escreve o tamanho e depois o registro*/
    fwrite(&content, sizeof(char), 1, fp);
    fwrite(&size, sizeof(int), 1, fp);
    fwrite(reg, size, 1, fp);

    fflush(fp);

    return pos;
}
