#ifndef B_TREE
#define B_TREE

#include <stdio.h>
#include <stdlib.h>

#define NIL -1
#define EMPTY_SPACE 127

extern int num_of_bt_trees;
extern int keylength;
extern int bt_length;

struct key_struct 
{
    char* key;
    int db_pos;
};

struct b_tree
{
    int num;

    struct key_struct* keys;
    int* address;
};


struct b_tree* create_btree(int num);

void save_btree_infile(struct b_tree* bt, FILE* fp, int pos);

void load_btree_infile(struct b_tree* bt, FILE* fp, int pos);

void free_btree(struct b_tree* bt);

FILE* create_btree_file(char* filename, int bt_len, int key_len);

FILE* open_btree_file(char* filename);


#endif /*B_TREE*/