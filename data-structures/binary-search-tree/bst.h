#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node
{
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    unsigned int key;
} Node;

typedef struct
{
    struct Node *root;
} BSTree;

// Function prototypes from main.c
Node *create_node(unsigned int key);
BSTree *initialize_tree();
void tree_insert(BSTree *tree, Node *newNode);

// Functions from printer.c
void print_tree(Node *node, int space);
void inorder_tree_walk(Node *node);
void postorder_tree_walk(Node *node);

#endif /* BST_H */
