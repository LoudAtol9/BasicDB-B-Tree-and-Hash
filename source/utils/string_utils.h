#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include "../utils/linked_list.h"

#define LESS 2
#define EQUAL 0
#define MORE 1

int my_strlen(char* str);
bool my_strcmp(char* str1, char* str2);

void str_format_in(char* reg, int size);
void str_format_out(char* reg, int size);

char* find_field(char* reg, int n);


/*
 * String 1 = String 2 : 0
 * String 1 > String 2 : 1
 * String 1 < String 2 : 2
 */
int string_compare(char* str1, char* str2);

#endif /*STRING_UTILS_H*/