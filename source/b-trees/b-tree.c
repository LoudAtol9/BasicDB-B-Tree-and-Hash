#include "b-tree.h"

int bt_length;
int keylength;
int num_of_bt_trees;

struct b_tree* create_btree(int num)
{
    int i = 0;
    int y = 0;

    struct b_tree* bt = NULL;

    bt = (struct b_tree*) malloc(sizeof(struct b_tree));

    bt->num = num;
    bt->keys = (struct key_struct*) malloc(sizeof(struct key_struct) * (bt_length + 1));
    bt->address = (int*) malloc(sizeof(int) * (bt_length + 2));

    for (i = 0; i < bt_length + 1; i++)
        bt->keys[i].key = (char*) malloc(sizeof(char) * keylength);

    for (i = 0; i < bt_length + 1; i++)
    {
        for (y = 0; y < keylength; y++)
            bt->keys[i].key[y] = EMPTY_SPACE;
        
        bt->keys[i].db_pos = NIL;
    }
    
    for (i = 0; i < (bt_length + 2); i++)
        bt->address[i] = NIL;
    
    return bt;
}

void save_btree_infile(struct b_tree* bt, FILE* fp, int pos)
{
    int i;

    fseek(fp, pos, SEEK_SET);

    fwrite(&num_of_bt_trees, sizeof(int), 1, fp);
    num_of_bt_trees++;

    for (i = 0; i < bt_length; i++)
    {
        fwrite(bt->keys[i].key, sizeof(char), keylength, fp);
        fwrite(&bt->keys[i].db_pos, sizeof(int), 1, fp);
    }
    
    fwrite(bt->address, sizeof(int), bt_length + 1, fp);
}

void load_btree_infile(struct b_tree* bt, FILE* fp, int pos)
{
    int i;

    fseek(fp, pos, SEEK_SET);

    fread(&bt->num, sizeof(int), 1, fp);

    for (i = 0; i < bt_length; i++)
    {
        fread(bt->keys[i].key, sizeof(char), keylength, fp);
        fread(&bt->keys[i].db_pos, sizeof(int), 1, fp);
    }
    
    fread(bt->address, sizeof(int), bt_length + 1, fp);
}


void free_btree(struct b_tree* bt)
{
    int i = 0;
    
    for (i = 0; i < bt_length; i++)
        free(bt->keys[i].key);

    free(bt->address);
    free(bt->keys);
    free(bt); 
}


FILE* create_btree_file(char* filename, int bt_len, int key_len)
{
    int head_pos = 3 * sizeof(int);
    struct b_tree* first;
    FILE* fp;

    fp = fopen(filename, "w+");
    fclose(fp);
    fp = fopen(filename, "r+");

    fwrite(&bt_len, sizeof(int), 1, fp);
    fwrite(&key_len, sizeof(int), 1, fp);
    fwrite(&head_pos, sizeof(int), 1, fp);

    bt_length = bt_len;
    keylength = key_len;
    
    first = create_btree(1);
    save_btree_infile(first, fp, head_pos);

    fflush(fp);

    free_btree(first);
    return fp;
}

FILE* open_btree_file(char* filename)
{
    FILE* fp;
    fp = fopen(filename, "r+");

    if (fp != NULL)
    {
        fread(&bt_length, sizeof(int), 1, fp);
        fread(&keylength, sizeof(int), 1, fp);

        fseek(fp, 0, SEEK_END);
        num_of_bt_trees = (ftell(fp) - (3 * sizeof(int))) / (bt_length * (keylength + (sizeof(int) * 2)) + (sizeof(int) * 2));
    }

    return fp;
}