#include "busca_indice.h"

void search_all_keys_in_order_recursive(FILE* fp, int page_pos, struct cel** list);

int search_key(FILE* fp, char* key)
{
    int i = 0; 
    int page_pos = 0;
    int cmp = 0;

    bool can_be_found = true;

    struct b_tree* page;

    if (key[keylength - 1] == '|')
        key[keylength - 1] = '\0';

    fseek(fp, 0, SEEK_SET);

    fread(&bt_length, sizeof(int), 1, fp);
    fread(&keylength, sizeof(int), 1, fp);
    fread(&page_pos, sizeof(int), 1, fp);

    page = create_btree(-1);

    // enquanto tem a chance de existir no arq
    while (can_be_found)
    {   
        // Carrega a page da posicao indica e copia pra estrutura de dado     
        load_btree_infile(page, fp, page_pos);
        
        for (i = 0; i < bt_length; i++)
        {
            // Compara chave com chave
            cmp = strcmp(page->keys[i].key, key);

            // Achou o intervalo que está a key
            if (cmp > 0 || page->keys[i].key[0] == EMPTY_SPACE)
            {
                page_pos = page->address[i];
                break;
            }
            // Achou a Key
            else if (cmp == 0)
            {
                printf("Chave %s encontrada na página %ld, posição %d\n", key, (page_pos - sizeof(int) * 3) / (bt_length * (keylength + (2 * sizeof(int))) + (sizeof(int) * 2)) , i);
                page_pos = page->keys[i].db_pos; 
                free_btree(page);
                return page_pos;

            }  
            
        }

        // A key está no ultimo espaço 
        // percorreu o for inteiro sem achar o intervalo
        if (i == bt_length)
            page_pos = page->address[i];
        
        // Se a page nao exister logo a chave procurada
        // nao existe e retorna NIL
        if (page_pos == NIL)
            can_be_found = false; 
    }
    
    // Chave procurada nao está no arq
    free_btree(page);
    return NIL;
}

struct cel* search_all_keys(FILE* fp)
{
    int i = 0;
    int cmp = 0;
    int* page_pos = NULL;
    int* db_pos = NULL;   
    
    bool can_be_found = true;

    struct cel* all_pos = NULL;
    struct queue* page_pos_q = NULL;
    struct b_tree* page = NULL;

    fseek(fp, 0, SEEK_SET);
    fread(&bt_length, sizeof(int), 1, fp);
    fread(&keylength, sizeof(int), 1, fp);

    page = create_btree(-1);

    page_pos = (int*) malloc(sizeof(int));
    fread(page_pos, sizeof(int), 1, fp);
    enqueue(&page_pos_q, page_pos);

    // Enquanto tiver paginas pra se ir
    while (page_pos_q != NULL)
    {
        // Pega o endereco da prox pagina da fila
        page_pos = dequeue(&page_pos_q);

        // Carega proxima pagina
        load_btree_infile(page, fp, *page_pos);

        // Salva todos os enderecos dos registros
        for (i = 0; i < bt_length; i++)
        {
            // Endereço eh valido?
            if (page->keys[i].db_pos != NIL)
            {
                db_pos = (int*) malloc(sizeof(int));
                *db_pos = page->keys[i].db_pos;
                add_elem(&all_pos, db_pos);
            }
        }

        // Coloca na fila todas as proximas paginas
        for (i = 0; i < bt_length + 1; i++)
        {
            // Endereco eh valido?
            if (page->address[i] != NIL)
            {
                page_pos = (int*) malloc(sizeof(int));
                *page_pos = page->address[i];
                enqueue(&page_pos_q, page_pos);
            }
        }
    }
    free_btree(page);
    return all_pos;
}

struct cel* search_all_keys_in_order(FILE* fp)
{
    int page_pos;
    struct cel* list = NULL;

    fseek(fp, 0, SEEK_SET);
    fread(&bt_length, sizeof(int), 1, fp);
    fread(&keylength, sizeof(int), 1, fp);
    fread(&page_pos, sizeof(int), 1, fp);

    search_all_keys_in_order_recursive(fp, page_pos, &list);

    return list;
}

void search_all_keys_in_order_recursive(FILE* fp, int page_pos, struct cel** list)
{
    int i;
    int* db_pos;
    struct b_tree* page;
    page = create_btree(-1);

    // Carega proxima pagina
    load_btree_infile(page, fp, page_pos);

    // Coloca na fila todas as proximas paginas
    for (i = 0; i < bt_length + 1; i++)
    {
        // Endereco eh valido?
        if (page->address[i] != NIL)
            search_all_keys_in_order_recursive(fp, page->address[i], list);

        // Endereço eh valido?
        if (page->keys[i].db_pos != NIL)
        {
            db_pos = (int*) malloc(sizeof(int));
            *db_pos = page->keys[i].db_pos;
            add_elem(list, db_pos);
        }
    }

    free_btree(page);
}
    


void read_reg_by_key(FILE* fp, FILE* bt_file, char* key, char** reg, int* size)
{
    int file_pos;

    file_pos = search_key(bt_file, key);

    fseek(fp, file_pos + sizeof(char), SEEK_SET);
    fread(size, sizeof(int), 1, fp);

    *reg = (char*) malloc(sizeof(char) * (*size));
    fread(*reg, sizeof(char), *size, fp);
}


void print_all_reg(FILE* fp, FILE* bt_file)
{
    int file_pos;
    int size;
    char* reg = NULL;

    struct cel* reg_pos = NULL;
    struct cel* aux = NULL;

    //reg_pos = search_all_keys(bt_file);
    reg_pos = search_all_keys_in_order(bt_file);

    for (aux = reg_pos; aux != NULL; aux = aux->next)
    {
        file_pos = *((int*) aux->info);

        fseek(fp, file_pos + sizeof(char), SEEK_SET);
        fread(&size, sizeof(int), 1, fp);

        reg = (char*) malloc(sizeof(char) * (size));
        fread(reg, sizeof(char), size, fp);

        print_any_register(reg, size);
        putchar('\n');

        free(reg);
    }
    
    free_list(reg_pos);
}
