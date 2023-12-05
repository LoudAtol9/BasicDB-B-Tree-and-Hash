#include "database/file_utils.h"
#include "database/insercao.h"
#include "database/busca.h"
#include "database/remocao.h"
#include "database/compressao.h"

#include "menu/menu_options.h"


int main()
{
    FILE* fdb = NULL;
    FILE* ind_pri = NULL;
    FILE* ind_sec_1 = NULL;
    FILE* ind_sec_2 = NULL;
    int length = 1;

    int tail = 0;
    char* filename = NULL;

    menu_file_options(&fdb, &tail, &filename);
    
    if (fdb == NULL)
    {
        return 0;
    }
    
    menu_function_options(fdb, &tail, filename);

    return 0;
}