#include <stdio.h>
#include <stdbool.h>
#define QUEUE_SIZE 5

typedef struct
{
    int head;
    int tail;
    int arr[QUEUE_SIZE];
} Queue;

void initialize_queue(Queue *queue)
{
    queue->head = 1;
    queue->tail = 1;
}

bool is_empty(Queue *queue)
{
    return queue->head == queue->tail;
}

bool is_full(Queue *queue)
{
    return queue->head == queue->tail + 1 || queue->head == 1 && queue->tail == QUEUE_SIZE;
}

void enqueue(Queue *queue, int value)
{
    if (is_full(queue))
    {
        printf("Queue Overflow!\n");
        return;
    }

    if (queue->tail == QUEUE_SIZE)
    {
        queue->tail = 1;
    }
    else
    {

        queue->tail++;
    }

    queue->arr[queue->tail - 1] = value;
}

int dequeue(Queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue Underflow!\n");
        return -1;
    }

    int dequeued = queue->arr[queue->head - 1];
    if (queue->head == QUEUE_SIZE)
    {
        queue->head = 1;
    }
    else
    {
        queue->head++;
    }

    return dequeued;
}

void print_queue(Queue *queue)
{
    printf("Queue: ");

    if (is_empty(queue))
    {
        printf("[empty]\n");
        return;
    }

    int i = queue->head;
    while (i != queue->tail)
    {
        printf("%d ", queue->arr[i - 1]);
        if (i == QUEUE_SIZE)
            i = 1;
        else
            i++;
    }

    printf("%d\n", queue->arr[queue->tail - 1]);
}

int main()
{
    Queue queue;
    initialize_queue(&queue);

    enqueue(&queue, 1);
    print_queue(&queue);

    enqueue(&queue, 2);
    print_queue(&queue);

    enqueue(&queue, 3);
    print_queue(&queue);

    enqueue(&queue, 4);
    print_queue(&queue);

    dequeue(&queue);
    print_queue(&queue);

    enqueue(&queue, 5);
    print_queue(&queue);

    dequeue(&queue);
    print_queue(&queue);

    enqueue(&queue, 6);
    print_queue(&queue);

    dequeue(&queue);
    print_queue(&queue);

    enqueue(&queue, 7);
    print_queue(&queue);

    dequeue(&queue);
    print_queue(&queue);

    enqueue(&queue, 8);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    print_queue(&queue);

    return 0;
}