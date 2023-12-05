#include "string_utils.h"

bool my_strcmp(char* str1, char* str2)
{
    int i;
    int size;

    size = my_strlen(str1);

    if (size != my_strlen(str2))
        return false;
    
    for (i = 0; i < size; i++)
    {
        if (str1[i] != str2[i])
            return false;    
    }

    return true;
}

int my_strlen(char* str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++);
    return i;
}

/*
 * String 1 = String 2 : 0
 * String 1 > String 2 : 1
 * String 1 < String 2 : 2
 */
int string_compare(char* str1, char* str2)
{
    int i = 0;
    int state = 0;

    char cmp1;
    char cmp2;

    while (str1[i] != '\0' || str2[i] != '\0')
    {
        if (str1[i] == str2[i])
            i++;
        else 
        {
            cmp1 = (str1[i] >= 65 & str1[i] <= 90) ? str1[i] + 32 : str1[i];
            cmp2 = (str2[i] >= 65 & str2[i] <= 90) ? str2[i] + 32 : str2[i];

            if (cmp1 > cmp2)
                return 1;
            else
                return 2;   
        }
    }

    if (str1[i] == '\0' && str2[i] == '\0')
        return 0;
    if (str2[i] != '\0')
        return 1;
    if (str1[i] != '\0')
        return 2;      

    return 4;
}

void str_format_in(char* reg, int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        if (reg[i] == '\0')
            reg[i] = '|';   
    }
}

void str_format_out(char* reg, int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        if (reg[i] == '|')
            reg[i] = '\0';   
    }
}


char* find_field(char* reg, int n)
{
    int i = 0;
    int count = n;
    char* field = reg;

    while (count != 0)
    {
        if (reg[i] == '\0')
        {
            count--;
            field = &(reg[i + 1]);  
        }
        i++;     
    }
    return field;
}


