#include "insere_key.h"


void recursive_insert_btree(FILE* fp, int page_pos, char* key, int* db_pos, int* new_page_pos);
bool add_key_in_btree(struct b_tree* bt, char* key, int db_pos, int address);
void split_btree(FILE* fp, char* key, int* db_pos, struct b_tree* left, int pos_left, int* pos_right);


int find_new_insert_pos(FILE* fp)
{
    int i; 
    int pos;
    char first_elem;

    // Pula o Header
    fseek(fp, sizeof(int) * 4, SEEK_SET);

    // Percorre todas as b-tree para achar um com o primeiro elemento vazio
    // Logo ela está vazia tbm
    for (i = 0; fread(&first_elem, sizeof(char), 1, fp); i++)
    {  
        // Achou o local
        if (first_elem == EMPTY_SPACE)
            return ftell(fp) - sizeof(char);
        // Pula pra próxima b-tree
        fseek(fp, bt_length * (keylength + (sizeof(int) * 2)) + (sizeof(int) * 2), SEEK_CUR);
    }
    // Não tem nenhuma b-tree vazia, logo vai escrever no final do arquivo
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

/*
 *  Insere a chave com seu valor no arquivo de btree
 *  Caso exista, ela não irá inserir.
 */
void insert_btree(FILE* fp, char* key, int db_pos)
{
    int page_pos;
    int* new_page_pos = NULL;

    struct b_tree* head;

    if (key[keylength - 1] == '|')
        key[keylength - 1] = '\0';
    
    new_page_pos = (int*) malloc(sizeof(int));

    /*Lê o cabeçalho do arquivo*/
    fseek(fp, 0, SEEK_SET);
    fread(&bt_length, sizeof(int), 1, fp);
    fread(&keylength, sizeof(int), 1, fp);
    fread(&page_pos, sizeof(int), 1, fp);
    *new_page_pos = NIL;

    recursive_insert_btree(fp, page_pos, key, &db_pos, new_page_pos);

    /*Splitou até o final*/
    if (*new_page_pos != NIL)
    {
        head = create_btree(-1);

        /*Adiciona o elemento na btree*/
        memcpy(head->keys[0].key, key, bt_length);
        head->keys[0].db_pos = db_pos;

        /*Pega o endereço da esq e da dir*/
        /*esq --> page_pos;  dir --> new_page_pos;*/
        head->address[0] = page_pos;
        head->address[1] = *new_page_pos;

        /*Salva a arv no arquivo*/
        page_pos = find_new_insert_pos(fp);
        save_btree_infile(head, fp, page_pos);

        /*Atualiza o cabeçalho pra essa arv*/
        fseek(fp, sizeof(int) * 2, SEEK_SET);
        fwrite(&page_pos, sizeof(int), 1, fp);

        free_btree(head);        
    }

    free(new_page_pos);
}


void recursive_insert_btree(FILE* fp, int page_pos, char* key, int* db_pos, int* new_page_pos)
{
    int i;
    int cmp;
    int next_pos = 0;

    struct b_tree* page;

    page = create_btree(-1);

    // Carrega a page da posicao indica e copia pra estrutura de dado     
    load_btree_infile(page, fp, page_pos);

    for (i = 0; i < bt_length; i++)
    {
        // Compara chave com chave
        cmp = strcmp(page->keys[i].key, key);

        // Achou o intervalo que deve ser inserida a key
        if (cmp > 0 || page->keys[i].key[0] == EMPTY_SPACE)
        {
            next_pos = page->address[i];
            break;
        }
        // Achou a Key,
        // Logo não pode inserir
        else if (cmp == 0)
        {
            printf("\nNão pode ser inserido, já existe\n");
            free_btree(page);
            return;
        }   
    }

    // A key está no ultimo espaço 
    // percorreu o for inteiro sem achar o intervalo
    if (i == bt_length)
        next_pos = page->address[i];
        
    // Se a page nao existir, temos que inserir
    // a chave nessa b-tree
    if (next_pos == NIL)
    {
        /*Será necessário splitar a b-tree após inserção?*/

        /*Sim*/
        if (add_key_in_btree(page, key, *db_pos, *new_page_pos))
        {
            split_btree(fp, key, db_pos, page, page_pos, new_page_pos);
            printf("\nFoi realizado o split\n");
            printf("\nChave %s Promovida\n", key);
        }     
        /*Não*/
        else
        {
            *new_page_pos = NIL;
            save_btree_infile(page, fp, page_pos);
        }
            
    }
    // Vamos pro próximo nó
    else
    {
        recursive_insert_btree(fp, next_pos, key, db_pos, new_page_pos);

        /*Temos que promover mais algum elemento?*/
        if (*new_page_pos != NIL)
        {
            /*Será necessário splitar a b-tree após inserção?*/

            /*Sim*/
            if (add_key_in_btree(page, key, *db_pos, *new_page_pos))
                split_btree(fp, key, db_pos, page, page_pos, new_page_pos);
            /*Não*/
            else
            {
                *new_page_pos = NIL;
                save_btree_infile(page, fp, page_pos);
            }
        }            
    }

    free_btree(page);    
}


bool add_key_in_btree(struct b_tree* bt, char* key, int db_pos, int address)
{
    int i;
    int j;
    int cmp;

    /*Acha o local de inserção*/
    for (i = 0; i < bt_length + 1; i++)
    {
        cmp = strcmp(bt->keys[i].key, key);

        /*Tem que reordenar a lista*/
        if (cmp > 0)
        {
            /*Libera espaço para inserir a chave*/
            /*Empurra além da b-tree se precisar*/
            for (j = bt_length - 1; j > i - 1; j--)
            {
                memcpy(bt->keys[j + 1].key, bt->keys[j].key, keylength);
                bt->keys[j + 1].db_pos = bt->keys[j].db_pos;
                bt->address[j + 2] = bt->address[j + 1];
            }

            /*Salva a chave e a posição correspondente*/
            memcpy(bt->keys[i].key, key, keylength);
            bt->keys[i].db_pos = db_pos;
            bt->address[i + 1] = address; 
            break;
        }
        /*É o proprio espaco vazio*/
        else if (bt->keys[i].key[0] == EMPTY_SPACE)
        {
            /*Não há necessidade de empurrar pra liberar espaço*/
            memcpy(bt->keys[i].key, key, keylength);
            bt->keys[i].db_pos = db_pos;
            break;
        }
    }

    /*Precisará fazer o split?*/
    return (bt->keys[bt_length].key[0] != EMPTY_SPACE);
}


void split_btree(FILE* fp, char* key, int* db_pos, struct b_tree* left, int pos_left, int* pos_right)
{
    int i;  
    int j;
    int half;
    struct b_tree* right = NULL;

    /*Define aonde será a metade*/
    if (bt_length % 2 == 0)
        half = bt_length / 2;
    else
        half = (bt_length / 2) + 1;

    right = create_btree(1);

    /*Salva o conjunto que será promovido*/
    memcpy(key, left->keys[half].key, keylength);
    *db_pos = left->keys[half].db_pos;

    /*Limpando o espaço*/
    for (j = 0; j < keylength; j++)
        left->keys[half].key[j] = EMPTY_SPACE;    
    left->keys[half].db_pos = NIL;

    /*Percorre a outra metade da btree e salva em outra*/
    for (i = half + 1; i < bt_length + 1; i++)
    {
        /*Pegar a "metade" da btree e copiando pra outra*/
        memcpy(right->keys[i - half - 1].key, left->keys[i].key, keylength);
        right->keys[i - half - 1].db_pos = left->keys[i].db_pos;
        right->address[i - half - 1] = left->address[i];

        /*Apagando os registros que transeferimos*/
        for (j = 0; j < keylength; j++)
            left->keys[i].key[j] = EMPTY_SPACE;
        
        left->keys[i].db_pos = NIL;
        left->address[i] = NIL;
    }

    /*Salva o ultimo endereco*/
    right->address[i - half - 1] = left->address[i];
    left->address[i] = NIL;

    /*Acha o melhor local pra inserir*/
    *pos_right = find_new_insert_pos(fp);

    /*Atualiza o "left" e cria o "right"*/
    save_btree_infile(left, fp, pos_left);
    save_btree_infile(right, fp, *pos_right);

    free_btree(right);
}

