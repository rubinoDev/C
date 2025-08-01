#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
    int value;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
} LinkedList;

Node *create_node(int value)
{
    Node *node = malloc(sizeof(Node));

    if (!node)
    {
        printf("Fail to allocate memory. \n");
        return NULL;
    }

    node->next = NULL;
    node->prev = NULL;
    node->value = value;

    return node;
}

void initialize_list(LinkedList *list, int value)
{
    Node *initialNode = create_node(value);

    if (list->head != NULL || list->tail != NULL)
    {
        printf("Not able to initialize list, the list was already initialized!\n");
        return;
    }

    list->head = initialNode;
    list->tail = initialNode;
}

void prepend(LinkedList *list, int value)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Not able to find head. Initialize the list first!\n");
        return;
    }
    Node *node = create_node(value);

    node->next = list->head;
    list->head->prev = node;
    list->head = node;
}

void append(LinkedList *list, int value)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Not able to find head. Initialize the list first!\n");
        return;
    }

    Node *node = create_node(value);

    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
}

Node *search(LinkedList *list, int value)
{
    if (list == NULL || list->head == NULL)
    {
        printf("Not able to find head. Initialize the list first!\n");
        return NULL;
    }

    Node *node = list->head;

    while (node != NULL)
    {
        if (node->value == value)
            return node;
        node = node->next;
    }

    return NULL;
}

void insert(Node *targetNode, int value)
{
    if (targetNode == NULL)
    {
        printf("You must pass a valid target node. \n");
        return;
    }

    Node *newNode = create_node(value);
    if (targetNode->next != NULL)
    {
        targetNode->next->prev = newNode;
    }
    newNode->prev = targetNode;
    newNode->next = targetNode->next;
    targetNode->next = newNode;
}

void delete(LinkedList *list, Node *node)
{
    if (list->head == list->tail)
    {
        free(node);
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }
    else
    {
        list->tail = node->prev;
    }

    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }
    else
    {
        list->head = node->next;
    }

    node->next = NULL;
    node->prev = NULL;
    free(node);
}

void destroy_list(LinkedList *list)
{
    Node *current = list->head;

    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    list->head = NULL;
    list->tail = NULL;
}

void display(LinkedList *list)
{

    Node *current = list->head;

    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    LinkedList list = {0};
    initialize_list(&list, 25);
    printf("Initialized with value: %d \n", list.head->value);
    prepend(&list, 10);
    printf("Prepended with value: %d \n", list.head->value);
    append(&list, 5);
    printf("Appended with value: %d \n", list.tail->value);
    Node *node = search(&list, 10);
    printf("Node value: %d \n", node->value);

    printf("Before insert:");
    display(&list);

    insert(node, 98);
    printf("After insert:");
    display(&list);

    delete(&list, node);
    printf("After delete:");
    display(&list);

    destroy_list(&list);

    printf("After destroy:");
    display(&list);

    return 0;
}
