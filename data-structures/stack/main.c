#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct
{
    int arr[MAX_SIZE];
    int top;
} Stack;

void initialize(Stack *stack)
{
    stack->top = -1;
}

bool is_full(Stack *stack)
{
    return stack->top >= MAX_SIZE - 1;
}

bool is_empty(Stack *stack)
{
    return stack->top == -1;
}

void push(Stack *stack, int value)
{
    if (is_full(stack))
    {
        printf("Stack Overflow, max size exceeded: %d !\n", MAX_SIZE);
        return;
    }

    stack->arr[++stack->top] = value;
}

int pop(Stack *stack)
{

    if (is_empty(stack))
    {
        printf("Stack Underflow, the stack is empty!\n");
        return -1;
    }

    int popped = stack->arr[stack->top];
    stack->top--;
    return popped;
}

int peek(Stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack is empty\n");
        return -1;
    }

    return stack->arr[stack->top];
}

int main()
{
    Stack stack;
    initialize(&stack);

    push(&stack, 3);
    printf("Top element: %d\n", peek(&stack));

    push(&stack, 5);
    printf("Top element: %d\n", peek(&stack));

    push(&stack, 2);
    printf("Top element: %d\n", peek(&stack));

    push(&stack, 8);
    printf("Top element: %d\n", peek(&stack));

    while (!is_empty(&stack))
    {
        printf("Top element: %d\n", peek(&stack));
        printf("Popped element: %d\n", pop(&stack));
    }

    return 0;
}