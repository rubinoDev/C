#include "bst.h"

void print_tree(Node *root, int space)
{
    if (root == NULL)
        return;

    int COUNT = 5;
    space += COUNT;

    print_tree(root->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    print_tree(root->left, space);
}

void inorder_tree_walk(Node *node)
{
    Node *current = node;
    if (current != NULL)
    {
        inorder_tree_walk(current->left);
        printf("%d ", current->key);
        inorder_tree_walk(current->right);
    }
}

void postorder_tree_walk(Node *node)
{
    Node *current = node;
    if (current != NULL)
    {
        postorder_tree_walk(current->right);
        printf("%d ", current->key);
        postorder_tree_walk(current->left);
    }
}
