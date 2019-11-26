#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

void print_arr(int* arr, int size) {
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    
    printf("\n");
}

struct queue {
    int* arr;

    int front;
    int rear;

    int capacity;
    int size;
};

typedef struct queue Queue;

Queue* init_queue(int capacity) {

    Queue* queue = (Queue*) malloc(sizeof(Queue));

    queue->arr = (int*) malloc(sizeof(int) * capacity);

    queue->front = -1;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;

    return queue;
}

int is_empty(Queue* queue) {
    return queue->size == 0;
}

int is_full(Queue* queue) {
    return queue->size == queue->capacity;
}

void enqueue(Queue* queue, int data) {

    if(queue) {

        if(is_full(queue)) {
            printf("Queue full size %d capacity %d\n", queue->size, queue->capacity);
            
        } else {

            if(queue->front == -1)
                queue->front++;

            queue->arr[++queue->rear] = data;
            queue->size++;

        }

    } else {
        printf("Queue error line 141\n");
    }
}

int dequeue(Queue* queue) {

    if(!is_empty(queue)) {

        int data = queue->arr[queue->front];
        queue->front++;
        queue->size--;

        return data;

    } else {

        printf("EMPTY queue\n");
        return -1;
    }
}

void print_queue(Queue* queue) {
    for(int i = queue->front; i <= queue->rear; i++)
        printf("%d ", queue->arr[i]);
    printf("\n");
}

#endif

