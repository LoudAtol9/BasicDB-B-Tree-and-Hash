#include "user_inputs.h"

char* insertion_user_input(int* size)
{
    int i = 0;
    int j = 0;

    char* reg;    

    char cod[4];
    char name[50];
    char sec[50];
    char type[30];

    printf("\nDigite o codigo do segurado: ");
    scanf("%s3[^\n]", cod);
    printf("Digite o nome do segurado: ");
    scanf("%s49[^\n]", name);
    printf("Digite o nome da seguradora: ");
    scanf("%s49[^\n]", sec);
    printf("Digite o tipo do seguro: ");
    scanf("%s29[^\n]", type);

    *size = my_strlen(cod) + my_strlen(name) + my_strlen(sec) + my_strlen(type) + 4;

    reg = (char*) malloc(sizeof(char) * (*size));

    for (i = 0; i < my_strlen(cod); i++)
    {
        reg[j] = cod[i];
        j++;
    }

    reg[j] = '|';
    j++;

    for (i = 0; i < my_strlen(name); i++)
    {
        reg[j] = name[i];
        j++;
    }

    reg[j] = '|';
    j++;

    for (i = 0; i < my_strlen(sec); i++)
    {
        reg[j] = sec[i];
        j++;
    }

    reg[j] = '|';
    j++;

    for (i = 0; i < my_strlen(type); i++)
    {
        reg[j] = type[i];
        j++;
    }

    reg[j] = '\0';
    j++;

    return reg;
}


void user_code_input(char* code)
{
    int i;
    bool done = false;

    printf("\nDigite o codigo do segurado: ");

    do
    {
        scanf("%s3[^\n]", code);
    
        done = true;

        for (i = 0; i < 3; i++)
        {
            if (code[i] < '0' && code[i] > '9')
            {
                printf("\n Codigo invalido, digite novamente :");
                done = false;
                break;
            }
        }
    } while (!done);  

    code[3] = '\0';
}