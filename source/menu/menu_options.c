#include "menu_options.h"


void naming_files(char** fdb_name)
{
    char filename[50];

    //pedindo o nome do arquivo
    printf("\nQual o nome do arquivo? Nome: ");
    fflush(stdout);
    scanf("%s29[^\n]", filename);

    //gerando o nome do arquivo
    *fdb_name = make_fdb_filename(filename);

}


//Salvar o nome do arquivo com um ponteiro (malloc de fdb_name)
void menu_file_options(FILE** fdb, int* tail, char** filename)
{
    int option;

    do{
        printf("\n- - - - - - - - Opcoes de Arquivo - - - - - - - -\n\n");
        printf("     1) Criar Arquivo    2) Carregar Arquivo\n");
        printf("     Opcao: ");
        scanf("%d", &option); 
        switch(option)
        {
            case 1:
                //nomeando os arquivos
                naming_files(filename);

                //criando o arquivo
                my_create(fdb, tail, *filename);

                printf("     Arquivo criado com sucesso.\n"); 
                break;
            case 2:
                //nomeando os arquivos
                naming_files(filename);

                //abrindo o arquivo
                my_fopen(fdb, tail, *filename);

                printf("     Arquivo carregado com sucesso.\n"); 
                break;
            default:
                printf("     Digite uma opcao valida.\n");
        }
    }while(option<1 || option>2);
}

void menu_function_options(FILE* file, int* tail, char* filename)
{
    FILE* hash_file;
    FILE* test_file;
    FILE* test_file_indicator;

    struct cel* p_keys;
    struct cel* s_keys;

    char begin = 'b';
    char end = 'e';
    char state = 'n';
    int option;
    int secundary_option;
    int pos = 0;
    int db_pos = 0;
    int size_of_reg = 0;
    int field = 2; 
    int tam;

    struct cel* ptr;

    char* register1 = NULL;
    char* code = NULL;
    char* code2 = NULL;
    
    bool sair = false;

    code = (char*) malloc(sizeof(char) * 4);

    hash_file = load_hashtable("../source/files/hash.ind");
    if (hash_file == NULL)
        hash_file = create_hashtable("../source/files/hash.ind", 13, 4, 2); 

    test_file = fopen("../source/files/insere.bin", "r+");
    test_file_indicator = fopen("../source/files/insere.aux", "r+");
    if (test_file_indicator == NULL)
    {
        test_file_indicator = fopen("../source/files/insere.aux", "w+");
        fwrite(&pos, sizeof(int), 1, test_file_indicator);
    }
    

    do{
        register1 = NULL;
        printf("\n+ - - - - - - - Opcoes de Funcoes - - - - - - - +\n\n");
        printf("     1) Insercao         2) Remocao\n");
        printf("     3) Impressao        4) Compactacao\n");
        printf("     5) Sair\n");
        printf("     Opcao: ");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                printf("Opcao 1.\n");   //
                printf("\n+ - - - - - - - Opcoes de Inserção - - - - - - - +\n\n");
                printf("     1) Inserção Manual :\n");
                printf("     2) Inserção Via Arquivo :\n");
                printf("     3) Voltar\n");
                scanf("%d", &secundary_option);

                code = (char*) malloc(sizeof(char) * 4);
                code2 = (char*) malloc(sizeof(char) * 4);

                switch (secundary_option)
                {
                case 1:
                    register1 = insertion_user_input(&size_of_reg);
                    memcpy(code, register1, 4);
                    memcpy(code2, register1, 4);

                    if (search_key_in_hash(hash_file, code) == -1)
                    {
                        db_pos = insert_in_file(file, register1, size_of_reg);
                        insert_key_in_hash(hash_file, register1, db_pos);
                        printf("\nFoi Inserido com sucesso a chave %s", code2);
                    }
                    else
                        printf("\nNão pode ser inserido, já existe essa chave...\n");
                    break;

                case 2:
                    register1 = read_test_file(test_file, test_file_indicator, &size_of_reg);
                    memcpy(code, register1, 4);
                    memcpy(code2, register1, 4);
                    if (search_key_in_hash(hash_file, code) == -1)
                    {
                        db_pos = insert_in_file(file, register1, size_of_reg);
                        insert_key_in_hash(hash_file, register1, db_pos);
                        printf("\nFoi Inserido com sucesso a chave %s", code2);
                    }
                    else
                        printf("\nNão pode ser inserido, já existe essa chave...\n");
                    break;

                
                default:
                    break;
                }

                free(code2);
                break;
            case 2:
                printf("Opcao 2.\n");   //
                printf("\n+ - - - - - - - Opcoes de Remocao - - - - - - - +\n\n");
                printf("     1) Remover por Posicao\n");
                printf("     2) Remover por Codigo do segurado\n");
                printf("     3) Voltar\n");
                scanf("%d", &secundary_option);
                switch (secundary_option)
                {
                /*case 1:
                    printf("\nDigite a posicao: ");
                    scanf("%d", &pos);
                    remove_register(file, tail, pos);
                    break;*/

                case 2:
                    user_code_input(code);
                    delete_key_in_hash(file, code);
                    break;
                
                default:
                    break;
                }    

                break;
            case 3:
                printf("Opcao 3.\n");   
                printf("\n+ - - - - - - - Opcoes de Busca - - - - - - - +\n\n");
                printf("     1) Busca por Posicao\n");
                printf("     2) Busca por Codigo do segurado\n");
                printf("     3) Imprimir Todos os Segurados\n");
                printf("     4) Voltar\n");
                scanf("%d", &secundary_option);
                putchar('\n');
                switch (secundary_option)
                {
                case 1:
                    printf("Digite a posicao: ");
                    scanf("%d", &pos);
                    read_reg_by_pos(file, pos, &register1, &size_of_reg);
                    print_any_register(register1, size_of_reg);  
                    break;

                case 2:
                    user_code_input(code);

                    /*read_reg_by_code(file, code, &register1, &size_of_reg);
                    fseek(file, pos + sizeof(char), SEEK_SET);
                    fread(&size_of_reg, sizeof(int), 1, file);
                    register1 = malloc(sizeof(char) * size_of_reg);
                    fread(register1, sizeof(char), size_of_reg, file);*/
  
                    pos = search_key_in_hash(hash_file, code);

                    print_any_register(register1, size_of_reg);  
                    break;

            /* case 3:
                    print_all_reg(file, hash_file);
                    break;*/
                    
                default:
                    break;
                }  
                break;
            case 4:
                printf("Opcao 4.\n");   //
                printf("\nDesfragmentacao iniciada! ");
                my_defrager(file, tail, filename);
                printf("\nDesfragmentacao Finalizada!");
                break;
            case 5:
                fclose(file);
                printf("Fechando o arquivo de registros e saindo...\n");
                sair = true;
                break;
            default:
                printf("     Digite uma opcao valida.\n");
        }
        if (register1 != NULL)
            free(register1);  
        
    }while(!sair);

    free(code);
}
