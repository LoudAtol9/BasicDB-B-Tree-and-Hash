#define COMPRESSAO_H

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include "../utils/linked_list.h"

int my_defrager(FILE* fp, int* tail, char* filename);

void delete_part_of_file(FILE* fp, int pos, int offset);

