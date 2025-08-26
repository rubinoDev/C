/*
 * Binary Search Tree Implementation
 *
 * Compilation:
 * gcc main.c printer.c -o main -lm
 *
 * The -lm flag is needed for the math library (pow function)
 */

#include "bst.h"

Node *create_node(unsigned int key)
{
    Node *node = malloc(sizeof(Node));

    if (!node)
    {
        printf("Fail to allocate memory to create node!");
        return NULL;
    }

    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->parent = NULL;

    return node;
}

BSTree *initialize_tree()
{
    BSTree *tree = malloc(sizeof(BSTree));
    if (!tree)
    {
        printf("Fail to allocate memory to initialize tree!");
        return NULL;
    }

    tree->root = NULL;

    return tree;
}

void tree_insert(BSTree *tree, Node *newNode)
{
    if (newNode == NULL)
    {
        fprintf(stderr, "Not able to insert a NULL node");
        return;
    }

    Node *current = tree->root;
    Node *aux = NULL;

    while (current != NULL)
    {
        aux = current;
        if (newNode->key >= current->key)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }

    newNode->parent = aux;

    if (aux == NULL)
    {
        tree->root = newNode;
    }
    else if (newNode->key >= aux->key)
    {
        aux->right = newNode;
    }
    else
    {
        aux->left = newNode;
    }
}

Node *tree_search(Node *node, unsigned int key)
{

    Node *current = node;

    if (current == NULL)
    {
        printf("Not able to find node with key: %d \n", key);
        return NULL;
    }

    if (current->key == key)
    {
        return current;
    }

    if (current->key <= key)
    {
        return tree_search(current->right, key);
    }
    else
    {
        return tree_search(current->left, key);
    }
}

Node *tree_min(Node *node)
{
    Node *current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

Node *tree_max(Node *node)
{
    Node *current = node;
    while (current->right != NULL)
    {
        current = current->right;
    }

    return current;
}

Node *tree_successor(Node *node)
{
    Node *current = node;

    if (current != NULL && current->right != NULL)
    {
        return tree_min(current->right);
    }

    Node *aux = node->parent;

    while (aux != NULL && current == aux->right)
    {
        current = aux;
        aux = aux->parent;
    }

    return aux;
}

Node *tree_predecessor(Node *node)
{
    Node *current = node;

    if (current != NULL && current->left != NULL)
    {
        return tree_max(current->left);
    }

    Node *aux = node->parent;

    while (aux != NULL && current == aux->left)
    {
        current = aux;
        aux = aux->parent;
    }

    return aux;
}

void transplant(BSTree *tree, Node *nodeToReplace, Node *replacementNode)
{
    if (nodeToReplace->parent == NULL)
    {
        tree->root = replacementNode;
    }
    else if (nodeToReplace == nodeToReplace->parent->left)
    {
        nodeToReplace->parent->left = replacementNode;
    }
    else
    {
        nodeToReplace->parent->right = replacementNode;
    }

    if (replacementNode != NULL)
    {
        replacementNode->parent = nodeToReplace->parent;
    }
}

void tree_delete(BSTree *tree, Node *nodeToDelete)
{

    if (nodeToDelete->left == NULL)
    {
        transplant(tree, nodeToDelete, nodeToDelete->right);
    }
    else if (nodeToDelete->right == NULL)
    {
        transplant(tree, nodeToDelete, nodeToDelete->left);
    }
    else
    {
        Node *successor = tree_min(nodeToDelete->right);
        if (successor != nodeToDelete->right)
        {
            transplant(tree, successor, successor->right);
            successor->right = nodeToDelete->right;
            successor->right->parent = nodeToDelete;
        }
        transplant(tree, nodeToDelete, successor);
        successor->left = nodeToDelete->left;
        successor->left->parent = successor;
    }
}

void destroy_tree(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    destroy_tree(node->right);
    destroy_tree(node->left);

    free(node);
}

void free_tree(BSTree *tree)
{
    if (tree == NULL)
    {
        return;
    }

    destroy_tree(tree->root);
    free(tree);
}

int main()
{
    BSTree *tree = initialize_tree();

    tree_insert(tree, create_node(10));
    tree_insert(tree, create_node(5));
    tree_insert(tree, create_node(15));
    tree_insert(tree, create_node(12));
    tree_insert(tree, create_node(20));
    tree_insert(tree, create_node(20));
    tree_insert(tree, create_node(20));
    tree_insert(tree, create_node(2));
    tree_insert(tree, create_node(2));
    tree_insert(tree, create_node(2));
    tree_insert(tree, create_node(2));
    tree_insert(tree, create_node(2));
    tree_insert(tree, create_node(1));

    printf("Árvore binária:\n");
    print_tree(tree->root, 0);

    printf("Inorder tree walk:\n");
    inorder_tree_walk(tree->root);

    printf("\n");

    printf("Order tree walk:\n");
    postorder_tree_walk(tree->root);

    printf("\n");

    Node *foundNode = tree_search(tree->root, 5);

    if (foundNode != NULL)
    {
        printf("Found node: %u\n", foundNode->key);
    }

    Node *minNode = tree_min(tree->root);

    if (minNode != NULL)
    {
        printf("Found min node: %u\n", minNode->key);
    }

    Node *maxNode = tree_max(tree->root);

    if (maxNode != NULL)
    {
        printf("Found max node: %u\n", maxNode->key);
    }

    Node *successor = tree_successor(foundNode);

    if (successor != NULL)
    {
        printf("Found successor node: %u\n", successor->key);
    }

    Node *predecessor = tree_predecessor(foundNode);

    if (predecessor != NULL)
    {
        printf("Found predecessor node: %u\n", predecessor->key);
    }

    free_tree(tree);

    return 0;
}
